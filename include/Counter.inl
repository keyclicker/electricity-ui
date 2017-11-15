
template<class T>
std::size_t Counter<T>::sCount = 0;

template<class T>
Counter<T>::Counter()
{
    ++sCount;
}
