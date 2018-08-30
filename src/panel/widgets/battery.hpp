#ifndef WIDGETS_BATTERY_HPP
#define WIDGETS_BATTERY_HPP

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>

#include <giomm/dbusproxy.h>
#include <giomm/dbusconnection.h>

#include "../widget.hpp"

using DBusConnection = Glib::RefPtr<Gio::DBus::Connection>;
using DBusProxy = Glib::RefPtr<Gio::DBus::Proxy>;

enum WfBatteryStatusDescription
{
    BATTERY_STATUS_ICON    = 0, // icon
    BATTERY_STATUS_PERCENT = 1, // icon + percentage
    BATTERY_STATUS_FULL    = 2, // icon + percentage + TimeToFull/TimeToEmpty
};

class wayfire_config;
class WayfireBatteryInfo : public WayfireWidget
{
    Gtk::Button button;
    Gtk::Label label;
    Gtk::HBox button_box;

    bool icon_invert = false;
    int icon_size;
    Gtk::Image icon;

    WfBatteryStatusDescription status;

    DBusConnection connection;
    DBusProxy upower_proxy, display_device;

    bool setup_dbus();

    void update_icon();
    void update_details();
    void update_state();

    void on_properties_changed(
        const Gio::DBus::Proxy::MapChangedProperties& properties,
        const std::vector<Glib::ustring>& invalidated);

    public:
    virtual void init(Gtk::HBox *container, wayfire_config *config);
    virtual ~WayfireBatteryInfo();
};


#endif /* end of include guard: WIDGETS_BATTERY_HPP */