# Threat Model: WiFi Washing Machine

**Scope:** a consumer washing machine on the home WiFi, controlled through the vendor's cloud and phone app. The owner cannot change the firmware or the hardware, so responses are limited to configuration and the network.

Response levels: **basic hygiene** < **software encryption** < **hardware locks**. The last two are the vendor's job, not the owner's.

## 1. Access to the home network
- **Asset:** the LAN the washer sits on, including the laptops, phones and NAS on it, plus the WiFi password stored in the washer.
- **Threat:** automated botnets that scan for any weak IoT device to recruit or to use as a foothold. They want your bandwidth and a pivot point. A targeted attacker is unrealistic. A neighbour in WiFi range is possible.
- **Attack surface:** a vendor cloud compromise pushed down to devices, open setup or AP mode during pairing, LAN services on the device, router UPnP exposing it, and outdated firmware.
- **What they could do:** use the washer as a bot, scan and attack other devices on the LAN, or recover the WiFi password from the device.
- **Response: basic hygiene.** Put the washer on a separate guest/IoT network so it can't reach your computers; this is the single most effective measure. Disable UPnP on the router and keep the washer's firmware updated. This is proportionate because the washer itself is worthless, but the network behind it isn't.

## 2. Vendor app account
- **Asset:** the login to the vendor cloud, which controls the machine.
- **Threat:** credential stuffing, i.e. reused passwords from other breaches tried automatically, and breaches of the vendor itself. Both are common and untargeted.
- **Attack surface:** the vendor's login page and API, and the phone app.
- **What they could do:** start or stop cycles, see usage history, and in the worst case use the account to reach other devices linked to the same vendor account.
- **Response: basic hygiene.** Use a unique password and enable 2FA if offered. That fully covers the realistic threat.

## 3. Usage data (privacy)
- **Asset:** when the machine runs, which reveals when someone is home.
- **Threat:** a burglar timing a break-in from washer data is theoretically possible but practically unrealistic; watching the house is easier. The realistic party is the vendor itself, collecting and possibly sharing usage data under its terms.
- **Attack surface:** vendor cloud storage and app permissions.
- **What they could do:** build a profile of your routines, or monetize it.
- **Response: accept, or disconnect.** Read the privacy settings and opt out of analytics where possible. If you don't actually use the remote features, the proportionate response is not connecting the washer at all; that removes every section of this document.
