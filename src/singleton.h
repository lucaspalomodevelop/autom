template <typename T>
class Singleton
{
public:
    static T &Instance()
    {
        static T _instance;
        return _instance;
    }

protected:
    Singleton() {}
    ~Singleton() {}

private:
    Singleton(Singleton const &);
    Singleton &operator=(Singleton const &);
};