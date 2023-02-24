/* #include "configuration.h"

void saveConfiguration(const char *filename, const std::vector<Time> &vec)
{
	// Delete existing file, otherwise the configuration is appended to the file
	if (LittleFS.exists(filename))
	{
		LittleFS.remove(filename);
	}

	// Open file for writing
	File file = LittleFS.open(filename, "w");
	if (!file)
	{
		Serial.println(F("Failed to create file"));
		return;
	}

	StaticJsonDocument<256> doc;

	// Set the values in the document
	for (size_t i = 0; i < vec.size(); i++)
	{
		doc.add(i);
		doc[i] = vec[i];
	}

	// Serialize JSON to file
	if (serializeJson(doc, file) == 0)
	{
		Serial.println(F("Failed to write to file"));
	}

	// Close the file
	file.close();
}

void loadConfiguration(const char *filename, std::vector<Time> &vec)
{
	// Open file for reading
	File file = LittleFS.open(filename, "r");

	// Allocate a temporary JsonDocument
	// Don't forget to change the capacity to match your requirements.
	// Use arduinojson.org/v6/assistant to compute the capacity.
	StaticJsonDocument<512> doc;

	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, file);
	if (error)
	{
		Serial.println(F("Failed to read file, using default configuration"));
	}

	// Copy values from the JsonDocument to the vector
	for (JsonVariant i : doc.as<JsonArray>())
	{
		Serial.println(i.as<String>());
		vec.push_back(i.as<String>());
	}

	// Close the file (Curiously, File's destructor doesn't close the file)
	file.close();
} */
