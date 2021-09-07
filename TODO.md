# TODOs

## Debug/status messages

- [x] Write debug/status messages to serial interface

## Read sd card

- [x] read configuration file from sd card

## Ethernet connection

- [x] initialize ethernet connection with fixed values

## Webserver

- [x] initialize webserver
- [x] return pin states
- [ ] return get parameters

## Switch

- [ ] turn led on
- [ ] add button to webinterface
- [ ] turn led on/off with button in web interface

## Impulse switch

- [ ] turn relay on/of with button in web interface
- [ ] turn impulse switch on/off with impulse on relay with button in web interface
- [ ] get status of impulse switch with separate input and dc/dc converter on impulse switch output

## MQTT

- [ ] connect to mqtt
- [ ] send systeminformation to mqtt

## MQTT impulse switch

- [ ] send impulse switch status in mqtt
- [ ] switch via mqtt

## Get configuration from sd card
- [ ] parse configuration file
- [ ] set variables from values from configuration file
    - mac address
    - ip address
    - mqtt server
        - ip address
        - username
        - password
        - topic
    - reset flag (reset eeprom stored values with those from sd card)
- [ ] only set values from SD card if there are no settings in eeprom or reset flag set

## Amazon Alexa

- [ ] Emulate Belkin WeMo or Philips Hue to connect to alexa
- [ ] switch with voice command

## DHCP

- [ ] use dhcp for ethernet connection

## DNS

- [ ] use dns for mqtt server
