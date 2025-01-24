#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <stdexcept>

class LocationValidator
{
public:
    static void validateLocation(int country_id, int currency_id, int language_id)
    {
        if (country_id < 0 || currency_id < 0 || language_id < 0)
        {
            throw std::invalid_argument("Country, currency, or language ID cannot be negative");
        }

        if (country_id > 999 || currency_id > 999 || language_id > 999)
        {
            throw std::invalid_argument("Country, currency, or language ID is too large");
        }
    }
};

class Location
{
public:
    Location(int country_id = 0, int currency_id = 0, int language_id = 0)
        : m_country_id(country_id), m_currency_id(currency_id), m_language_id(language_id)
    {
        LocationValidator::validateLocation(country_id, currency_id, language_id);
    }

    int getCountryId() const { return m_country_id; }
    int getCurrencyId() const { return m_currency_id; }
    int getLanguageId() const { return m_language_id; }

private:
    int m_country_id;
    int m_currency_id;
    int m_language_id;
};

#endif // LOCATION_HPP
