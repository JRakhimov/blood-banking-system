#include "../gtkInjector.h"
#include <gtk/gtk.h>

GtkWidget *phone_number;
GtkWidget *password;
GtkWidget *button;
GtkWidget *registerButton;

static void on_user_register_button_clicked(void) {
	gtk_widget_hide(userLoginWindow);
	gtk_widget_show(userRegistrationWindow);
}

static void on_user_login_button_clicked(void) {
  const gchar *phone=gtk_entry_get_text(GTK_ENTRY(phone_number));
  const gchar *pass=gtk_entry_get_text(GTK_ENTRY(password));

  g_print("Phone:%s\n", phone);
  g_print("Password:%s\n", pass);
}

void initUserLoginWindow() {
  userLoginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "user_login"));

  phone_number = GTK_WIDGET(gtk_builder_get_object(builder, "user_phone"));
  password = GTK_WIDGET(gtk_builder_get_object(builder, "password"));
  button = GTK_WIDGET(gtk_builder_get_object(builder,"Login_button"));
  registerButton = GTK_WIDGET(gtk_builder_get_object(builder,"reg_btn"));

  g_signal_connect(button, "clicked", G_CALLBACK(on_user_login_button_clicked), NULL);
  g_signal_connect(registerButton, "clicked", G_CALLBACK(on_user_register_button_clicked), NULL);
}
