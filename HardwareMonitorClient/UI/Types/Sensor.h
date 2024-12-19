#pragma once

#include <QString>

struct Sensor
{
    QString name;
    std::optional<float> value;
    std::optional<float> min;
    std::optional<float> max;
    std::optional<QString> unit;
    std::optional<quint32> precision;

    bool hasValue() const
    {
        return value.has_value();
    }

    bool hasMin() const
    {
        return min.has_value();
    }

    bool hasMax() const
    {
        return max.has_value();
    }

    bool hasUnit() const
    {
        return unit.has_value();
    }

    bool hasPrecision() const
    {
        return precision.has_value();
    }

    float getValue() const
    {
        return value.value();
    }

    float getMin() const
    {
        return min.value();
    }

    float getMax() const
    {
        return max.value();
    }

    QString getUnit() const
    {
        return unit.value();
    }

    quint32 getPrecision() const
    {
        return precision.value();
    }
};
