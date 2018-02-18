// Copyright (C) 2018 by Sunil
#ifndef HASH_H
#define HASH_H

#include <functional>

template <typename T>
using hash = std::function<std::size_t(T)>;

#endif /* HASH_H */
