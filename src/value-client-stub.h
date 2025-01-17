/* Generated by dbus-binding-tool; do not edit! */

#include <glib.h>
#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

#ifndef _DBUS_GLIB_ASYNC_DATA_FREE
#define _DBUS_GLIB_ASYNC_DATA_FREE
static inline void
_dbus_glib_async_data_free (gpointer stuff)
{
	g_slice_free (DBusGAsyncData, stuff);
}
#endif

#ifndef DBUS_GLIB_CLIENT_WRAPPERS_uk_ac_cam_db538_VolumeNotification
#define DBUS_GLIB_CLIENT_WRAPPERS_uk_ac_cam_db538_VolumeNotification

static inline gboolean
uk_ac_cam_db538_VolumeNotification_notify (DBusGProxy *proxy, const gint IN_volume, const gboolean IN_muted, const gboolean IN_brightness, GError **error)

{
  return dbus_g_proxy_call (proxy, "notify", error, G_TYPE_INT, IN_volume, G_TYPE_BOOLEAN, IN_muted, G_TYPE_BOOLEAN, IN_brightness, G_TYPE_INVALID, G_TYPE_INVALID);
}

typedef void (*uk_ac_cam_db538_VolumeNotification_notify_reply) (DBusGProxy *proxy, GError *error, gpointer userdata);

static void
uk_ac_cam_db538_VolumeNotification_notify_async_callback (DBusGProxy *proxy, DBusGProxyCall *call, void *user_data)
{
  DBusGAsyncData *data = (DBusGAsyncData*) user_data;
  GError *error = NULL;
  dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
  (*(uk_ac_cam_db538_VolumeNotification_notify_reply)data->cb) (proxy, error, data->userdata);
  return;
}

static inline DBusGProxyCall*
uk_ac_cam_db538_VolumeNotification_notify_async (DBusGProxy *proxy, const gint IN_volume, const gboolean IN_muted, const gboolean IN_brightness, uk_ac_cam_db538_VolumeNotification_notify_reply callback, gpointer userdata)

{
  DBusGAsyncData *stuff;
  stuff = g_slice_new (DBusGAsyncData);
  stuff->cb = G_CALLBACK (callback);
  stuff->userdata = userdata;
  return dbus_g_proxy_begin_call (proxy, "notify", uk_ac_cam_db538_VolumeNotification_notify_async_callback, stuff, _dbus_glib_async_data_free, G_TYPE_INT, IN_volume, G_TYPE_BOOLEAN, IN_muted, G_TYPE_BOOLEAN, IN_brightness, G_TYPE_INVALID);
}
#endif /* defined DBUS_GLIB_CLIENT_WRAPPERS_uk_ac_cam_db538_VolumeNotification */

G_END_DECLS
