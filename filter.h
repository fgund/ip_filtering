#ifndef FILTER_H
#define FILTER_H
template <typename Container, typename Predicate>
Container filter(const Container &container, Predicate predicate) 
{
    Container result;
    std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
    return result;
}
#endif //FILTER_H