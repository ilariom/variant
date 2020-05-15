#ifndef number_h
#define number_h

namespace estd
{

class number
{
public:
    number() = default;
    explicit number(double d) : real_(d) { }
    explicit number(int i) : real_(static_cast<float>(i)) { }
    explicit number(long i) : real_(static_cast<float>(i)) { }
    explicit number(long long i) : real_(static_cast<float>(i)) { }
    explicit number(unsigned int i) : real_(static_cast<float>(i)) { }
    explicit number(unsigned long i) : real_(static_cast<float>(i)) { }
    explicit number(unsigned long long i) : real_(static_cast<float>(i)) { }
    
public:
    number& operator=(double d) { real_ = d; return *this; }
    number& operator=(int i) { real_ = static_cast<double>(i); return *this; }
    number& operator=(long i) { real_ = static_cast<double>(i); return *this; }
    number& operator=(long long i) { real_ = static_cast<double>(i); return *this; }
    number& operator=(unsigned int i) { real_ = static_cast<double>(i); return *this; }
    number& operator=(unsigned long i) { real_ = static_cast<double>(i); return *this; }
    number& operator=(unsigned long long i) { real_ = static_cast<double>(i); return *this; }
    
    operator double() const { return real_; }
    operator float() const { return static_cast<float>(real_); }
    operator int() const { return static_cast<int>(real_); }
    operator short() const { return static_cast<short>(real_); }
    operator char() const { return static_cast<char>(real_); }
    operator long() const { return static_cast<long>(real_); }
    operator long long() const { return static_cast<long long>(real_); }
    operator unsigned char() const { return static_cast<unsigned char>(real_); }
    operator unsigned short() const { return static_cast<unsigned short>(real_); }
    operator unsigned int() const { return static_cast<unsigned int>(real_); }
    operator unsigned long() const { return static_cast<unsigned long>(real_); }
    operator unsigned long long() const { return static_cast<unsigned long long>(real_); }
    
private:
    double real_ = 0;
};

} // namespace estd

#endif