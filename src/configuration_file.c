#include <string.h>
#include <regex.h>
#include "dlist.c"

typedef struct
{
	char *key, *value;
} ConfigEntry;

#define unlikely(x)  __builtin_expect(!!(x), 0)

/**
 * @brief Quit with RETV_BADALLOC if the passed-in pointer is empty.
 */
static inline void *
allocchk_(void *ptr, const char *func_name) {
  if (unlikely(!ptr)) {
    printf("%s(): Failed to allocate memory.", func_name);
	exit(4);
  }

  return ptr;
}

/// @brief Wrapper of allocchk_().
#define allocchk(ptr) allocchk_(ptr, __func__)

static char *
copy_match(const char *line, regmatch_t *match)
{
	char *r;
	r = (char *)malloc(match->rm_eo + 1);
	strncpy(r, line + match->rm_so, match->rm_eo - match->rm_so);
	r[match->rm_eo - match->rm_so] = 0;
	return r;
}

static ConfigEntry *
entry_new(char *key, char *value)
{
	ConfigEntry *e = (ConfigEntry *)malloc(sizeof(ConfigEntry));
	e->key = key;
	e->value = value;
	return e;
}

static dlist *
entry_set(dlist *config, char *key, char *value)
{
	dlist *iter = dlist_first(config);
	ConfigEntry *entry;
	for(; iter; iter = iter->next)
	{
		entry = (ConfigEntry *)iter->data;
		if(! strcasecmp(entry->key, key)) {
			free(key);
			free(entry->value);
			entry->value = value;
			return config;
		}
	}
	entry = entry_new(key, value);
	return dlist_add(config, entry);
}

static dlist *
config_parse(const char *config) {
	regex_t re_empty, re_entry;
	regmatch_t matches[5];
	char line[8192];
	int ix = 0, l_ix = 0;
	dlist *new_config = 0;
	
	regcomp(&re_empty, "^[[:space:]]*#|^[[:space:]]*$", REG_EXTENDED);
	regcomp(&re_entry, "^[[:space:]]*([[:alnum:]]+)[[:space:]]*=[[:space:]]*(.*?)[[:space:]]*$", REG_EXTENDED);
	
	while(1)
	{
		// strchr() considers '\0' at the end of the string as well
		if (strchr("\n\r", config[ix])) {
			line[l_ix] = 0;
			if(regexec(&re_empty, line, 5, matches, 0) == 0) {
				/* do nothing */
			}  else if(regexec(&re_entry, line, 5, matches, 0) == 0) {
				char *key = copy_match(line, &matches[1]),
				     *value = copy_match(line, &matches[2]);
				new_config = entry_set(new_config, key, value);
			} else  {
				fprintf(stderr, "WARNING: Ignoring invalid line: %s\n", line);
			}
			l_ix = 0;
		} else {
			line[l_ix] = config[ix];
			l_ix++;
		}
		if (!config[ix])
			break;
		++ix;
	}
	
	regfree(&re_empty);
	regfree(&re_entry);
	
	return new_config;
}

dlist *
config_load(const char *path)
{
	FILE *fin = fopen(path, "r");
	long flen;
	char *data;
	dlist *config;
	
	if(! fin)
	{
		fprintf(stderr, "WARNING: Couldn't load config file '%s'.\n", path);
		return 0;
	}
	else
	{
		printf("(): config file found. using \"%s\"", path);
	}
	
	fseek(fin, 0, SEEK_END);
	flen = ftell(fin);
	
	if(! flen)
	{
		fprintf(stderr, "WARNING: '%s' is empty.\n", path);
		fclose(fin);
		return 0;
	}
	
	fseek(fin, 0, SEEK_SET);
	
	data = allocchk(malloc(flen + 1));
	data[flen] = '\0';
	if(fread(data, 1, flen, fin) != flen)
	{
		fprintf(stderr, "WARNING: Couldn't read from config file '%s'.\n", path);
		free(data);
		fclose(fin);
		return 0;
	}
	
	fclose(fin);
	
	config = config_parse(data);
	
	free(data);
	
	return config;
}

static void
entry_free(ConfigEntry *entry)
{
	free(entry->key);
	free(entry->value);
	free(entry);
}

void
config_free(dlist *config)
{
	dlist_free_with_func(config, (dlist_free_func)entry_free);
}

static int
entry_find_func(dlist *l, ConfigEntry *key)
{
	ConfigEntry *entry = (ConfigEntry*)l->data;
	return ! strcasecmp(entry->key, key->key);
}

const char *
config_get(dlist *config, const char *key, const char *def)
{
	ConfigEntry needle;
	dlist *iter;
	
	needle.key = (char *)key;
	
	iter = dlist_find(dlist_first(config), (dlist_match_func)entry_find_func, &needle);
	
	if(! iter)
		return def;
	
	return ((ConfigEntry*)iter->data)->value;
}
