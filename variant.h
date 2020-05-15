#ifndef variant_h
#define variant_h

#include "number.h"
#include <string>
#include <ostream>

namespace estd
{

class variant
{
public:
    enum class type
    {
        BOOLEAN, REAL, INTEGER, STRING, VOID
    };
    
public:
    variant() = default;
    explicit variant(const std::string& value) : s_(value), type_(type::STRING) { }
    explicit variant(const char* str) : variant(std::string { str }) { }
    explicit variant(double value) : real_(value), type_(type::REAL) { }
    explicit variant(bool value) : boolean_(value), type_(type::BOOLEAN) { }
    explicit variant(int value) : integer_(value), type_(type::INTEGER) { }

public:
    variant& operator=(const std::string&);
    variant& operator=(const char* str) { return this->operator=(std::string { str }); }
    variant& operator=(double);
    variant& operator=(bool);
    variant& operator=(int);
    
    explicit operator bool() const { return type_ != type::VOID; }
    bool operator==(const variant&) const;
    bool operator!=(const variant& other) const { return !(*this == other); }
    
    bool operator<=(const variant&) const;
    bool operator>=(const variant&) const;
    
public:
    type get_type() const { return type_; }
    
    const std::string& as_string() const;
    double as_real() const;
    int as_integer() const;
    bool as_boolean() const;
    number as_number() const;
    
    bool is_numeric() const { return type_ == type::REAL || type_ == type::INTEGER; }
    
protected:
    void set_type(type t) { type_ = t; }
    
private:
    type type_ = type::VOID;
    std::string s_;
    
    union {
        double real_;
        int integer_;
        bool boolean_;
    };
};

std::ostream& operator<<(std::ostream& os, const variant& variant);
std::ostream& verbose(std::ostream& os, const variant& variant);

inline variant& variant::operator=(const std::string& value)
{
    type_ = type::STRING;
    s_ = value;
    
    return *this;
}

inline variant& variant::operator=(double value)
{
    type_ = type::REAL;
    real_ = value;
    
    return *this;
}

inline variant& variant::operator=(bool value)
{
    type_ = type::BOOLEAN;
    boolean_ = value;
    
    return *this;
}

inline variant& variant::operator=(int value)
{
    type_ = type::INTEGER;
    integer_ = value;
    
    return *this;
}

inline const std::string& variant::as_string() const
{
    assert(type_ == type::STRING);
    return s_;
}

inline double variant::as_real() const
{
    assert(type_ == type::REAL);
    return real_;
}

inline int variant::as_integer() const
{
    assert(type_ == type::INTEGER);
    return integer_;
}

inline bool variant::as_boolean() const
{
    assert(type_ == type::BOOLEAN);
    return boolean_;
}

inline number variant::as_number() const
{
    assert(is_numeric());
    
    if (get_type() == type::INTEGER)
    {
        return number { as_integer() };
    }
    
    if (get_type() == type::REAL)
    {
        return number { as_real() };
    }
    
    return {};
}

inline bool variant::operator==(const variant& other) const
{
    if (type_ != other.type_)
    {
        return false;
    }
    
    switch (type_)
    {
        case type::STRING:
            return s_ == other.s_;
            
        case type::INTEGER:
            return integer_ == other.integer_;
            
        case type::REAL:
            return real_ == other.real_;
            
        case type::BOOLEAN:
            return boolean_ == other.boolean_;
            
        case type::VOID:
            return true;
            
        default:
            return false;
    }

    return false;
}

inline bool variant::operator<=(const variant& other) const
{
    if (type_ != other.type_)
    {
        return false;
    }
    
    switch (type_)
    {
        case type::STRING:
            return s_ <= other.s_;
            
        case type::INTEGER:
            return integer_ <= other.integer_;
            
        case type::REAL:
            return real_ <= other.real_;
            
        case type::BOOLEAN:
            return boolean_ <= other.boolean_;
            
        case type::VOID:
            return true;
            
        default:
            return false;
    }

    return false;
}

inline bool variant::operator>=(const variant& other) const
{
    if (type_ != other.type_)
    {
        return false;
    }
    
    switch (type_)
    {
        case type::STRING:
            return s_ >= other.s_;
            
        case type::INTEGER:
            return integer_ >= other.integer_;
            
        case type::REAL:
            return real_ >= other.real_;
            
        case type::BOOLEAN:
            return boolean_ >= other.boolean_;
            
        case type::VOID:
            return true;
            
        default:
            return false;
    }

    return false;
}

inline std::ostream& verbose(std::ostream& os, const variant& var)
{
    switch (var.get_type())
    {
        case variant::type::STRING:
            os << '\'' << var.as_string() << '\'' << " : string";
            break;
            
        case variant::type::INTEGER:
            os << var.as_integer() << " : int";
            break;
            
        case variant::type::REAL:
            os << var.as_real() << " : real";
            break;
            
        case variant::type::BOOLEAN:
            os << var.as_boolean() << " : bool";
            break;
            
        default:
        case variant::type::VOID:
            os <<  "() : void";
            break;
    }
    
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const variant& var)
{
    switch (var.get_type())
    {
        case variant::type::STRING:
            os << var.as_string();
            break;
            
        case variant::type::INTEGER:
            os << var.as_integer();
            break;
            
        case variant::type::REAL:
            os << var.as_real();
            break;
            
        case variant::type::BOOLEAN:
            os << var.as_boolean();
            break;
            
        default:
        case variant::type::VOID:
            break;
    }
    
    return os;
}

} // namespace estd

#endif