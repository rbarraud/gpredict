/*
    Gpredict: Real-time satellite tracking and orbit prediction program

    Copyright (C)  2001-2013  Alexandru Csete, OZ9AEC.

    Authors: Alexandru Csete <oz9aec@gmail.com>

    Comments, questions and bugreports should be submitted via
    http://sourceforge.net/projects/gpredict/
    More details can be found at the project home page:

            http://gpredict.oz9aec.net/
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
  
    You should have received a copy of the GNU General Public License
    along with this program; if not, visit http://www.fsf.org/
*/
#ifndef __GTK_EVENT_LIST_H__
#define __GTK_EVENT_LIST_H__ 1

#include <glib.h>
#include <glib/gi18n.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include "gtk-sat-data.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* *INDENT-ON* */

#define GTK_TYPE_EVENT_LIST       (gtk_event_list_get_type ())
#define GTK_EVENT_LIST(obj)       G_TYPE_CHECK_INSTANCE_CAST (obj,\
                                                  gtk_event_list_get_type (),\
                                                  GtkEventList)

#define GTK_EVENT_LIST_CLASS(klass)  G_TYPE_CHECK_CLASS_CAST (klass,\
                                                           gtk_event_list_get_type (),\
                                                           GtkEventListClass)

#define IS_GTK_EVENT_LIST(obj)       G_TYPE_CHECK_INSTANCE_TYPE (obj, gtk_event_list_get_type ())

typedef struct _gtk_event_list GtkEventList;
typedef struct _GtkEventListClass GtkEventListClass;

struct _gtk_event_list {
    GtkVBox         vbox;

    GtkWidget      *treeview;   /*!< the tree view itself */
    GtkWidget      *swin;       /*!< scrolled window */

    GHashTable     *satellites; /*!< Satellites. */
    qth_t          *qth;        /*!< Pointer to current location. */

    guint32         flags;      /*!< Flags indicating which columns are visible */

    gdouble         tstamp;     /*!< time stamp of calculations; set by GtkSatModule */
    GKeyFile       *cfgdata;
    gint            sort_column;
    GtkSortType     sort_order;
    GtkTreeModel   *sortable;

    void            (*update) (GtkWidget * widget);     /*!< update function */

};

struct _GtkEventListClass {
    GtkVBoxClass    parent_class;
};

/** Symbolic references to columns */
typedef enum {
    EVENT_LIST_COL_NAME = 0,    /*!< Satellite name. */
    EVENT_LIST_COL_CATNUM,      /*!< Catalogue number. */
    EVENT_LIST_COL_AZ,          /*!< Satellite Azimuth. */
    EVENT_LIST_COL_EL,          /*!< Satellite Elevation. */
    EVENT_LIST_COL_EVT,         /*!< Next event (AOS or LOS). */
    EVENT_LIST_COL_TIME,        /*!< Time countdown. */
    EVENT_LIST_COL_DECAY,       /*!< Whether satellite is decayed or not. */
    EVENT_LIST_COL_BOLD,        /*!< Stores weight for rendering text. */
    EVENT_LIST_COL_NUMBER
} event_list_col_t;

/** Column Flags */
typedef enum {
    EVENT_LIST_FLAG_NAME = 1 << EVENT_LIST_COL_NAME,    /*!< Satellite name. */
    EVENT_LIST_FLAG_CATNUM = 1 << EVENT_LIST_COL_CATNUM,
    EVENT_LIST_FLAG_AZ = 1 << EVENT_LIST_COL_AZ,
    EVENT_LIST_FLAG_EL = 1 << EVENT_LIST_COL_EL,
    EVENT_LIST_FLAG_EVT = 1 << EVENT_LIST_COL_EVT,      /*!< Next event (AOS or LOS) */
    EVENT_LIST_FLAG_TIME = 1 << EVENT_LIST_COL_TIME,    /*!< Time countdown */
} event_list_flag_t;

GType           gtk_event_list_get_type(void);
GtkWidget      *gtk_event_list_new(GKeyFile * cfgdata,
                                   GHashTable * sats,
                                   qth_t * qth, guint32 columns);
void            gtk_event_list_update(GtkWidget * widget);
void            gtk_event_list_reconf(GtkWidget * widget, GKeyFile * cfgdat);

void            gtk_event_list_reload_sats(GtkWidget * satlist,
                                           GHashTable * sats);
void            gtk_event_list_select_sat(GtkWidget * widget, gint catnum);

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif /* __cplusplus */
/* *INDENT-ON* */

#endif /* __GTK_SAT_MODULE_H__ */
