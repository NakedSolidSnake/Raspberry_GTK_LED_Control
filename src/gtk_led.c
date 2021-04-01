#include <gtk/gtk.h>
#include <led_interface.h>

typedef struct 
{
    void *object;
    LED_Interface *led;
} GTK_Context;

GtkWidget *g_lbl_led_status;
GtkWidget *g_lbl_title;

bool GTK_LED_Run(void *object, int argc, char **argv, LED_Interface *led)
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    GTK_Context context =
    {
        .object = object,
        .led = led
    };

    led->Init(object);

    gtk_init(&argc, &argv);

    // builder = gtk_builder_new();
    // gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    // Update October 2019: The line below replaces the 2 lines above
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, &context);

    g_lbl_title = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_title"));
    g_lbl_led_status = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_led_status"));

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}


void on_set_on(GtkWidget *widget, void *user_data)
{
    GTK_Context* context = (GTK_Context *)user_data;
    context->led->Set(context->object, 1);    
    gtk_label_set_text(GTK_LABEL(g_lbl_led_status), "On");
}

void on_set_off(GtkWidget *widget, void *user_data)
{
    GTK_Context* context = (GTK_Context *)user_data;
    context->led->Set(context->object, 0); 
    gtk_label_set_text(GTK_LABEL(g_lbl_led_status), "Off");
}

void on_window_main_destroy()
{
    gtk_main_quit();
}