/**
 *  Volnoti - Lightweight Volume Notification
 *  Copyright (C) 2011  David Brazdil <db538@cam.ac.uk>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <gtk/gtk.h>
#include <cairo.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

typedef struct {
    gint image_size;
    gint width;
    gint height;
    gint border;
    gint corner_radius;
    gint x;
    gint y;
    gdouble x0;
    gdouble y0;
    double alpha;
    gint image_padding;
    gint body_x_offset;
    gint max_icon_size;
    gint max_progressbar_size;

} Settings;

typedef struct {
    GtkWidget *win;
    GtkWidget *main_vbox;
    GtkWidget *iconbox;
    GtkWidget *icon;
    GtkWidget *progressbarbox;
    GtkWidget *progressbar;

    int width;
    int height;
    int last_width;
    int last_height;

    gboolean composited;
    Settings settings;
    glong timeout;
} WindowData;

Settings get_default_settings();
GtkWindow* create_notification(Settings settings);
void move_notification(GtkWindow *win, WindowData *windata, int x, int y);
void set_notification_icon(GtkWindow *nw, GdkPixbuf *pixbuf);
void set_progressbar_image (GtkWindow *nw, GdkPixbuf *pixbuf);
void destroy_notification(GtkWindow *win);

#endif /* NOTIFICATION_H */
