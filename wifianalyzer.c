#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void button_clicked(GtkWidget *button, gpointer user_data) {
    FILE *fp;
    char path[1035];
    fp = popen("sudo grep psk= /etc/NetworkManager/system-connections/* | grep `sudo nmcli c show --active | grep wifi | awk '{print $1}'` | cut -d= -f2", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    button = gtk_button_new_with_label("Find Wi-Fi Password");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show(button);
    gtk_widget_show(window);
    gtk_main();
    return 0;
}
