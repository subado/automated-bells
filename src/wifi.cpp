#include <wifi.hpp>

bool wifiSta(const char *ssid, const char *psk, const char *hostname)
{
	WiFi.mode(WIFI_STA);
	WiFi.setHostname(hostname);
	WiFi.begin(ssid, psk);
	Serial.print("Connecting");
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.print("WiFi failed!");
		return false;
	}
	Serial.printf("\nConnected to %s ( ip %s )\n", ssid, WiFi.localIP().toString().c_str());
	return true;
}

bool wifiAp(const char *ssid, const char *psk, const IPAddress &localIp)
{
	WiFi.softAPConfig(localIp, localIp, IPAddress(255, 255, 255, 0));

	if (!((strcmp(psk, "")) ? (WiFi.softAP(ssid)) : (WiFi.softAP(ssid, psk))))
	{
		Serial.println("Failed to create access point");
		return false;
	}

	Serial.printf("Access point created ( %s )\n", ssid);
	return true;
}
