#include "../gtkInjector.h"
#include <gtk/gtk.h>

GtkWidget *username;
GtkWidget *password;
GtkWidget *button;

static void on_admin_login_button_clicked(void) {
  const gchar *username=gtk_entry_get_text(GTK_ENTRY(username));
  const gchar *pass=gtk_entry_get_text(GTK_ENTRY(password));

  g_print("Username:%s\n", username);
  g_print("Password:%s\n", pass);	
}

void initAdminLoginWindow() {
  adminLoginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "admin_login"));

  username=GTK_WIDGET(gtk_builder_get_object(builder, "admin_user"));
  password=GTK_WIDGET(gtk_builder_get_object(builder, "password1"));
  button=GTK_WIDGET(gtk_builder_get_object(builder,"Login_button1"));

  g_signal_connect(button, "clicked", G_CALLBACK(on_admin_login_button_clicked),NULL);
}
