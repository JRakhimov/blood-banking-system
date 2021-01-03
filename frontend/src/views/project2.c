#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

GtkWidget	*window1;
GtkWidget	*box;
GtkWidget	*grid;
GtkWidget	*button;
GtkWidget	*label;
GtkWidget	*radio_btn3;
GtkWidget	*radio_btn4;
GtkBuilder	*builder;

int main (int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file( "project_ui.glade" );
	
	window1 = GTK_WIDGET( gtk_builder_get_object ( builder, "choose_role1" ));

	g_signal_connect(window1, "destroy", G_CALLBACK ( gtk_main_quit ), NULL );

	gtk_builder_connect_signals(builder, NULL);

	
	box = GTK_WIDGET(gtk_builder_get_object (builder, "choose_role_box1"));
	grid = GTK_WIDGET(gtk_builder_get_object (builder, "choose_role_grid1"));
	button = GTK_WIDGET(gtk_builder_get_object (builder, "role_cont_btn1"));
	label = GTK_WIDGET(gtk_builder_get_object (builder, "role_logo_label1"));
	radio_btn3 = GTK_WIDGET(gtk_builder_get_object (builder, "admin_radio_btn1"));
	radio_btn4 = GTK_WIDGET(gtk_builder_get_object (builder, "user_radio_btn1"));

	gtk_widget_show(window1);
	
	gtk_main();

	return EXIT_SUCCESS;
}

void on_button_clicked (GtkButton *b) {
     gtk_label_set_text (GTK_LABEL(label), (const gchar*) "Blood Bank2");
}


void on_admin_radio_btn1_toggled(GtkRadioButton *b) {
     gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
}

void on_user_radio_btn1_toggled(GtkRadioButton *b) {
     gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
}




	
