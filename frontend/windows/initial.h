#include "../gtkInjector.h"

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

GtkWidget	*window;
GtkWidget	*box;
GtkWidget	*grid;
GtkWidget	*button;
GtkWidget	*label;
GtkWidget	*radio_btn1;
GtkWidget	*radio_btn2;

void initInitialWindow() {
	initialWindow = GTK_WIDGET(gtk_builder_get_object(builder, "choose_role"));

	box = GTK_WIDGET(gtk_builder_get_object (builder, "choose_role_box"));
	grid = GTK_WIDGET(gtk_builder_get_object (builder, "choose_role_grid"));
	button = GTK_WIDGET(gtk_builder_get_object (builder, "role_cont_btn"));
	label = GTK_WIDGET(gtk_builder_get_object (builder, "role_logo_label"));
	
	radio_btn1 = GTK_WIDGET(gtk_builder_get_object (builder, "admin_radio_btn"));
	radio_btn2 = GTK_WIDGET(gtk_builder_get_object (builder, "user_radio_btn"));
}

void on_button_clicked (GtkButton *b) {
     gtk_label_set_text (GTK_LABEL(label), (const gchar*) "Blood Bank");
}


void on_admin_radio_btn_toggled(GtkRadioButton *b) {
     gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
}

void on_user_radio_btn_toggled(GtkRadioButton *b) {
     gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
}




	
