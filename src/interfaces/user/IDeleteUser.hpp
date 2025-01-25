#ifndef IDELETEUSER_HPP
#define IDELETEUSER_HPP

class IDeleteUser
{
public:
    virtual void deleteUser() = 0;
    virtual ~IDeleteUser() = default;
};

#endif // IDELETEUSER_HPP