#pragma once

#include <list>
#include <limits>
#include <vector>

#include <glm/glm.hpp>

#ifdef DEBUG
namespace test {
    struct draw_data {
        // opencv stuff
        // corners of the current boundary
        struct rect_t {
            glm::vec2 low;
            glm::vec2 high;
        } rect;
        // points in the grid
        std::vector<glm::vec2> points;
    };   
};
#endif

namespace quad {
    struct boundary {
        using vec_t = glm::vec2;
        vec_t _pos;
        vec_t _dim;
        vec_t _initial_dim;
        
        boundary() = default;
        boundary(const vec_t &cnt, const vec_t &dim) {
            _pos = cnt;
            _dim = dim;
            _initial_dim = dim;
        }
        boundary(const vec_t &cnt, const vec_t &dim, const vec_t &initial_dim) {
            _pos = cnt;
            _dim = dim;
            _initial_dim = initial_dim;
        }
        
        bool is_in(const vec_t &pt) const {
            const bool high = glm::all(glm::lessThanEqual(pt, _pos + _dim));
            const bool low = glm::all(glm::greaterThanEqual(pt, _pos - _dim));
            return (low && high);
        }
        
        bool intersects(const boundary &other) const {
            const vec_t other_max = other._pos + other._dim;
            const vec_t this_min = _pos - _dim;
            
            //printf("intersects: [%f,%f]\n", other._pos.x, other._pos.y);
            
            if(other_max.x < this_min.x) return false;
            if(other_max.y < this_min.y) return false;
            
            const vec_t other_min = other._pos - other._dim;
            const vec_t this_max = _pos + _dim;
            if(other_min.x > this_max.x) return false;
            if(other_min.y > this_max.y) return false;
            
            return true;
        }
        
        //! return list of new boundaries for tree sub-division
        std::vector<boundary> divide() const {
            const vec_t dim_half = _dim / 2.f;
            vec_t new_cnt_1 = _pos;
            new_cnt_1.x += dim_half.x;
            new_cnt_1.y += dim_half.y;
            
            vec_t new_cnt_2 = _pos;
            new_cnt_2.x += dim_half.x;
            new_cnt_2.y -= dim_half.y;
            
            vec_t new_cnt_3 = _pos;
            new_cnt_3.x -= dim_half.x;
            new_cnt_3.y -= dim_half.y;
            
            vec_t new_cnt_4 = _pos;
            new_cnt_4.x -= dim_half.x;
            new_cnt_4.y += dim_half.y;
            
            return {
                { new_cnt_1, dim_half, _initial_dim },
                { new_cnt_2, dim_half, _initial_dim },
                { new_cnt_3, dim_half, _initial_dim },
                { new_cnt_4, dim_half, _initial_dim }
            };
        }
    };
};

namespace oct {
    struct boundary {
        using vec_t = glm::vec3;
        vec_t _pos;
        vec_t _dim;
        vec_t _initial_dim;
        
        boundary() = default;
        boundary(const vec_t &cnt, const vec_t &dim) {
            _pos = cnt;
            _dim = dim;
            _initial_dim = dim;
        }
        boundary(const vec_t &cnt, const vec_t &dim, const vec_t &initial_dim) {
            _pos = cnt;
            _dim = dim;
            _initial_dim = initial_dim;
        }
        
        bool is_in(const vec_t &pt) const {
            const bool high = glm::all(glm::lessThanEqual(pt, _pos + _dim));
            const bool low = glm::all(glm::greaterThanEqual(pt, _pos - _dim));
            return (low && high);
        }
        
        bool intersects(const boundary &other) const {
            const vec_t other_max = other._pos + other._dim;
            const vec_t this_min = _pos - _dim;
            
            if(other_max.x < this_min.x) return false;
            if(other_max.y < this_min.y) return false;
            if(other_max.z < this_min.z) return false;
            
            const vec_t other_min = other._pos - other._dim;
            const vec_t this_max = _pos + _dim;
            if(other_min.x > this_max.x) return false;
            if(other_min.y > this_max.y) return false;
            if(other_min.z > this_max.z) return false;
            
            return true;
        }
        
        //! return list of new boundaries for tree sub-division
        std::vector<boundary> divide() const {
            const vec_t dim_half = _dim / 2.f;
            vec_t new_cnt_1 = _pos;
            new_cnt_1.x += dim_half.x;
            new_cnt_1.y += dim_half.y;
            new_cnt_1.z -= dim_half.z;
            
            vec_t new_cnt_2 = _pos;
            new_cnt_2.x += dim_half.x;
            new_cnt_2.y -= dim_half.y;
            new_cnt_2.z -= dim_half.z;
            
            vec_t new_cnt_3 = _pos;
            new_cnt_3.x -= dim_half.x;
            new_cnt_3.y -= dim_half.y;
            new_cnt_3.z -= dim_half.z;
            
            vec_t new_cnt_4 = _pos;
            new_cnt_4.x -= dim_half.x;
            new_cnt_4.y += dim_half.y;
            new_cnt_4.z -= dim_half.z;
            
            vec_t new_cnt_5 = _pos;
            new_cnt_5.x += dim_half.x;
            new_cnt_5.y += dim_half.y;
            new_cnt_5.z += dim_half.z;
            
            vec_t new_cnt_6 = _pos;
            new_cnt_6.x += dim_half.x;
            new_cnt_6.y -= dim_half.y;
            new_cnt_6.z += dim_half.z;
            
            vec_t new_cnt_7 = _pos;
            new_cnt_7.x -= dim_half.x;
            new_cnt_7.y -= dim_half.y;
            new_cnt_7.z += dim_half.z;
            
            vec_t new_cnt_8 = _pos;
            new_cnt_8.x -= dim_half.x;
            new_cnt_8.y += dim_half.y;
            new_cnt_8.z += dim_half.z;
            
            return {
                { new_cnt_1, dim_half, _initial_dim },
                { new_cnt_2, dim_half, _initial_dim },
                { new_cnt_3, dim_half, _initial_dim },
                { new_cnt_4, dim_half, _initial_dim },
                { new_cnt_5, dim_half, _initial_dim },
                { new_cnt_6, dim_half, _initial_dim },
                { new_cnt_7, dim_half, _initial_dim },
                { new_cnt_8, dim_half, _initial_dim }
            };
        }
    };
};

template <typename boundary_t, typename payload_t>
class tree {
    using pos_t = typename boundary_t::vec_t;
    
    struct compare_glm {
        bool operator() (const pos_t& lhs, const pos_t& rhs) const {
            return glm::all(glm::lessThan(lhs, rhs));
        }
    };
        
public:
    // boundary of the tree volume
    // defined by a center position and [w, h, l] dimension (half box size)
    boundary_t _boundary;
    
    // list of points
    std::vector<payload_t> _data = {};
    
    // tree branches
    std::vector<tree<boundary_t, payload_t>> _branches = {};
    
    // maximum capacity
    // default is three points (because we want a new boundary for each face)
    size_t _capacity;
    
    // number of underlying elements
    size_t _elements = 0;
    
protected:
    void divide() {
        // avoid getting boundaries too small
        size_t cap = _capacity;
/*
        if(glm::any(glm::lessThanEqual(_boundary._dim / pos_t(2), pos_t(1)))) {
            cap = std::numeric_limits<uint16_t>::max();
        }
*/
        for(const boundary_t &new_boundary : _boundary.divide()) {
            _branches.push_back(tree<boundary_t, payload_t>(new_boundary, cap));
        }
    }
    
    void recursive_find(const boundary_t &boundary_in, std::vector<payload_t> &points_in_out) const {        
        if(!_boundary.intersects(boundary_in)) {
            return;
        }
        for(const auto &e : _data) {
            points_in_out.push_back(e);
        }
        
        // forward the point to all branches
        for(const tree<boundary_t, payload_t> &b : _branches) {
            b.recursive_find(boundary_in, points_in_out);
        }
    }

    // the unnamed parameter pack "int..." guards against attempts to explicitly specify "I"
    void recursive_find(const pos_t &pos_in, std::vector<payload_t> &data_in_out) const {        
        if(!_boundary.is_in(pos_in)) {
            return;
        }
        for(const auto &e : _data) {
            data_in_out.push_back(e);
        }
        
        // forward the point to all branches
        for(const tree<boundary_t, payload_t> &b : _branches) {
            b.recursive_find(pos_in, data_in_out);
        }
    }
    
public:
    tree() = default;
    tree(const boundary_t &boundary, size_t capacity = 1) {
        _boundary = boundary;
        _capacity = capacity;
    }
    
    int elements() const {
        return _elements;
    }
    
    bool empty() const {
        return _elements < 1;
    }
    
    //! find all entries whose boundaries surround <pos>
    std::vector<payload_t> find(const pos_t &pos, const pos_t &search_dist) const {        
        std::vector<payload_t> res = {};
        recursive_find(boundary_t(pos, search_dist), res);
        return res;
    }
    
    //! find all entries whose boundaries intersect with <boundary>
    std::vector<payload_t> find(const boundary_t &boundary) const {
        std::vector<payload_t> res = {};
        recursive_find(boundary, res);
        return res;
    }
    
    //! insert a new point (and payload) into the tree
    bool insert(const pos_t &pos, const payload_t &val) {
        // point not in boundary
        if(!_boundary.is_in(pos)) {
            return false;
        }
        // push point in if not full
        if(_data.size() < _capacity) {
            _data.push_back(val);
            _elements++;
        }
        else {
            // if full then subdivide
            if(_branches.size() == 0) {
                divide();
            }
            // forward the point to all branches
            for(tree<boundary_t, payload_t> &b : _branches) {
                if(b.insert(pos, val)) break;
            }
        }
        return true;
    }
    
#ifdef DEBUG
    void recursive_get_tree(std::vector<test::draw_data> &corners) const {
        const auto &c = _boundary._pos;
        const auto &d = _boundary._dim;
        
        test::draw_data dta;
        dta.rect.low = c-d;
        dta.rect.high = c+d;        
        corners.push_back(dta);
        // forward the point to all branches
        for(const tree<boundary_t, payload_t> &b : _branches) {
            b.recursive_get_tree(corners);
        }
    }
#endif
};

#ifdef DEBUG
#include "oqtree_tests.h"
#endif
