#include "../gtkInjector.h"
#include <gtk/gtk.h>

GtkWidget *adminLoginUsernameInput;
GtkWidget *adminLoginPasswordInput;
GtkWidget *button;

static void on_admin_login_button_clicked(void) {
  const gchar *username = gtk_entry_get_text(GTK_ENTRY(adminLoginUsernameInput));
  const gchar *pass=gtk_entry_get_text(GTK_ENTRY(adminLoginPasswordInput));

  g_print("Username:%s\n", username);
  g_print("Password:%s\n", pass);	
}

void initAdminLoginWindow() {
  adminLoginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "admin_login"));

  adminLoginUsernameInput=GTK_WIDGET(gtk_builder_get_object(builder, "admin_user"));
  adminLoginPasswordInput=GTK_WIDGET(gtk_builder_get_object(builder, "password1"));
  button=GTK_WIDGET(gtk_builder_get_object(builder,"Login_button1"));

  g_signal_connect(button, "clicked", G_CALLBACK(on_admin_login_button_clicked),NULL);
}
