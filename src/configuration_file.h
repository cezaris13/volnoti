#ifndef VOLNOTI_CONFIG_H
#define VOLNOTI_CONFIG_H

#include <strings.h>
#include <ctype.h>

#include "dlist.h"
#include "configuration_file.c"

dlist *config_load(const char *);
void config_free(dlist *);

const char *config_get(dlist *, const char *, const char *);

/**
 * @brief Get a boolean value from configuration.
 */
static inline bool
config_get_bool(dlist *config, const char *key,
		bool def) {
	const char *strdef = (def ? "true": "false");
	const char *result = config_get(config, key, strdef);
	if (!strcasecmp("true", result))
		return true;
	if (!strcasecmp("false", result))
		return false;
	printf("(%s, %d): Unrecogized boolean value \"%s\".",
			key, def, result);
	return def;
}

/**
 * @brief Wrapper of config_get_bool().
 */
static inline void
config_get_bool_wrap(dlist *config, const char *key,
		bool *tgt) {
	*tgt = config_get_bool(config, key, *tgt);
}

/**
 * @brief Get an int value from configuration.
 */
static inline int
config_get_int(dlist *config, const char *key,
		int def, int min, int max) {
	const char *result = config_get(config, key, NULL);
	if (!result)
		return def;
	char *endptr = NULL;
	int iresult = strtol(result, &endptr, 0);
	if (!endptr || (*endptr && !isspace(*endptr))) {
		printf("(%s, %d): Value \"%s\" is not a valid integer.",
			key, def, result);
		return def;
	}
	if (iresult > max) {
		printf("(%s, %d): Value \"%s\" larger than maximum value %d.",
			key, def, result, max);
		return max;
	}
	if (iresult < min) {
		printf("(%s, %d): Value \"%s\" smaller than minimal value %d.",
			key, def, result, min);
		return min;
	}
	return iresult;
}

/**
 * @brief Wrapper of config_get_int().
 */
static inline void
config_get_int_wrap(dlist *config, const char *key,
		int *tgt, int min, int max) {
	*tgt = config_get_int(config, key, *tgt, min, max);
}

/**
 * @brief Get a double value from configuration.
 */
static inline double
config_get_double(dlist *config, const char *key,
		double def, double min, double max) {
	const char *result = config_get(config, key, NULL);
	if (!result)
		return def;
	char *endptr = NULL;
	double dresult = strtod(result, &endptr);
	if (!endptr || (*endptr && !isspace(*endptr))) {
		printf("(%s, %f): Value \"%s\" is not a valid floating-point number.",
			key, def, result);
		return def;
	}
	if (dresult > max) {
		printf("(%s, %f): Value \"%s\" larger than maximum value %f.",
			key, def, result, max);
		return max;
	}
	if (dresult < min) {
		printf("(%s, %f): Value \"%s\" smaller than minimal value %f.",
			key, def, result, min);
		return min;
	}
	return dresult;
}

/**
 * @brief Wrapper of config_get_double().
 */
static inline void
config_get_double_wrap(dlist *config, const char *key,
		double *tgt, double min, double max) {
	*tgt = config_get_double(config, key, *tgt, min, max);
}

#endif /* VOLNOTI_CONFIG_H */
