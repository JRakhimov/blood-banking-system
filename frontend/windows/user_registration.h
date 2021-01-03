#include "../gtkInjector.h"

#include <gtk/gtk.h>

GtkWidget *phone_number;
GtkWidget *birth_date;
GtkWidget *password;
GtkWidget *button;

static void on_btn_reg_clicked(void) {
  const gchar *phone=gtk_entry_get_text(GTK_ENTRY(phone_number));
  const gchar *birth=gtk_entry_get_text(GTK_ENTRY(birth_date));
  const gchar *pass=gtk_entry_get_text(GTK_ENTRY(password));

  g_print("Username:%s\n", phone);
  g_print("Birth_date:%s\n", birth);
  g_print("Password:%s\n", pass);
}

void initUserRegistrationWindow() {
  userRegistrationWindow = GTK_WIDGET(gtk_builder_get_object(builder, "user_registration"));

  phone_number=GTK_WIDGET(gtk_builder_get_object(builder, "user_reg_phone"));
  password=GTK_WIDGET(gtk_builder_get_object(builder, "reg_psw_entry"));
  birth_date = GTK_WIDGET(gtk_builder_get_object(builder, "date_of_birth"));
  button=GTK_WIDGET(gtk_builder_get_object(builder,"btn_reg"));

  g_signal_connect(button, "clicked", G_CALLBACK(on_btn_reg_clicked),NULL);
}


