//
// Created by swagner on 8/14/21.
//
// Shameless steal from: https://cppsecrets.com/users/41129711010797106994610011511264103109971051084699111109/C00-Config-Reader.php
//

#ifndef TIDAL_CONFIGREADER_H
#define TIDAL_CONFIGREADER_H

#include <iostream>
#include <map>

class ConfigReader {
private:

    // Define the map to store data from the config file
    std::map<std::string, std::string> m_ConfigSettingMap;

    // Static pointer instance to make this class singleton.
    static ConfigReader *m_pInstance;

public:

    // Public static method getInstance(). This function is
    // responsible for object creation.
    static ConfigReader *getInstance();

    // Parse the config file.
    bool parseFile(const std::string& fileName = "/tmp/default_config");

    // Overloaded getValue() function.
    // Value of the tag in configuration file could be
    // string or integer. So the caller need to take care this.
    // Caller need to call appropriate function based on the
    // data type of the value of the tag.

    bool getValue(const std::string& tag, int &value);

    bool getValue(const std::string& tag, std::string &value);

    // Function dumpFileValues is for only debug purpose
    void dumpFileValues();

private:

    // Define constructor in the private section to make this
    // class as singleton.
    ConfigReader();

    // Define destructor in private section, so no one can delete
    // the instance of this class.
    ~ConfigReader();

    // Define copy constructor in the private section, so that no one can
    // violate the singleton policy of this class
    ConfigReader(const ConfigReader &obj) {}

    // Define assignment operator in the private section, so that no one can
    // violate the singleton policy of this class
    void operator=(const ConfigReader &obj) {}

    // Helper function to trim the tag and value. This helper function is
    // calling to trim the un-necessary spaces.
    static std::string trim(const std::string &str, const std::string &whitespace = " \t");

    static std::string reduce(const std::string &str,
                       const std::string &fill = " ",
                       const std::string &whitespace = " \t");
};


#endif //TIDAL_CONFIGREADER_H
