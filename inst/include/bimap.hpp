/**
* datastructures: Implementation of core datastructures for R.
* <p>
* Copyright (C) Simon Dirmeier
* <p>
* This file is part of datastructures.
* <p>
* datastructures is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* <p>
* datastructures is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* <p>
* You should have received a copy of the GNU General Public License
* along with datastructures. If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef DS_BIMAP
#define DS_BIMAP

#include <Rcpp.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <boost/bimap.hpp>


template <typename T, typename U>
class bimap
{
public:
    bimap(): map_()
    {}

    size_t size()
    {
        return map_.size();
    }

    void insert(std::vector<T>& t, std::vector<U>& u)
    {
        if (t.size() != u.size())
        {
            Rcpp::stop("left.size() != right.size()");
        }
        for (typename std::vector<T>::size_type i = 0; i < t.size(); ++i)
        {
            map_.insert(boost::bimap< T, U >::value_type(t[i], u[i]));
        }
    }

    std::vector<T> lefts()
    {
        std::vector<T> lefts;
        keys.reserve(map_.size());
        for(boost::bimap<T, U>::left_map::const_iterator left_iter = map_.left.begin(),
            iend = map_.left.end();
            left_iter != iend; ++left_iter)
        {
            lefts.push_back(left_iter->first);
        }
        return lefts;
    }

    std::vector<U> rights()
    {
        std::vector<T> rights;
        rights.reserve(map_.size());
        for(boost::bimap<T, U>::right_map::const_iterator right_iter = map_.right.begin(),
            iend = map_.right.end();
            right_iter != iend;
            ++right_iter)
        {
            rights.push_back(right_iter->first);
        }
        return rights;
    }

    Rcpp::List head()
    {
        unsigned int i = 0;
        std::unordered_map< T, U > heads;
        for (boost::bimap<T, U>::left_map::const_iterator left_iter = map_.left.begin(),
             iend = map_.left.end();
             left_iter != iend; ++left_iter)
        {
            if (i++ == 5) break;
            heads.insert(std::pair<T, U>(left_iter->first, left_iter->second));
        }
        return Rcpp::wrap(heads);
    }

    std::vector<U> get_right(std::vector<T>& t)
    {
        std::vector<U> values;
        values.reserve(t.size());

        for (typename std::vector<T>::size_type i = 0; i < t.size(); ++i)
        {
            T key = t[i];
            if (map_.left.find(key) != map_.left.end())
            {
                values[i] =  map_.left.at(key);
            }
            else
            {
                std::stringstream ss;
                ss << key;
                Rcpp::stop(std::string("Could not find key: ").append(ss.str()));
            }
        }

        return values;
    }

    std::vector<T> get_left(std::vector<U>& u)
    {
        std::vector<T> values;
        values.reserve(u.size());

        for (typename std::vector<U>::size_type i = 0; i < u.size(); ++i)
        {
            U key = u[i];
            if (map_.right.find(key) != map_.right.end())
            {
                values[i] =  map_.right.at(key);
            }
            else
            {
                std::stringstream ss;
                ss << key;
                Rcpp::stop(std::string("Could not find key: ").append(ss.str()));
            }
        }

        return values;
    }


private:
    boost::bimap<T, U> map_;
};

typedef bimap<std::string, std::string> bimap_ss;
typedef bimap<std::string, int>         bimap_si;
typedef bimap<std::string, bool>        bimap_sb;
typedef bimap<std::string, double>      bimap_sd;

typedef bimap<double, std::string>  bimap_ds;
typedef bimap<double, int>          bimap_di;
typedef bimap<double, bool>         bimap_db;
typedef bimap<double, double>       bimap_dd;

typedef bimap<int, std::string>  bimap_is;
typedef bimap<int, int>          bimap_ii;
typedef bimap<int, bool>         bimap_ib;
typedef bimap<int, double>       bimap_id;

#endif