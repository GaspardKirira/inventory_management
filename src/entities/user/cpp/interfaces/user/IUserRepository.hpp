#ifndef IUSERREPOSITORY_HPP
#define IUSERREPOSITORY_HPP

class IUserRepository
{
public:
    virtual void findUser(int id) = 0;
    ~IUserRepository() = default;
};

#endif // IUSERREPOSITORY_HPP