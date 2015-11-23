//
// Created by lukaszlampart on 23.11.15.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include <vector>
#include <ostream>
#include <exception>
template<class T> class matrix {
public:
    //acces interface class allowing for matrix-like behaviour:
    //matrix a;
    //cout<<a[1][2];
    template<bool b> class input_interface {
    public:
        //std::conditional allows generating two seperete class types in one piece of code
        typedef typename std::conditional<b,typename std::vector<T>::iterator,typename std::vector<T>::const_iterator>::type it_type;
        typedef typename std::conditional<b, T, const T>::type value_type;
        typedef value_type& reference;
        reference operator[](std::size_t i) const {
            return *(data_pointer+i);
        }
        input_interface() = delete;
        input_interface(const it_type& init): data_pointer(init){}

    private:
        // iterator pointing to the data the object is coresponding
        it_type data_pointer;
    };
    typedef input_interface<true> non_const_interface;
    typedef input_interface<false> const_interface;
    //Constructors:
    matrix(): m(2), n(2), data(4) {}
    matrix(const size_t& a,const size_t& b): m(a), n(b), data(a*b) {}
    matrix(const size_t& a, const size_t& b, const T& init_value): m(a),n(b), data(a*b,init_value) {}
    matrix(const matrix& orgin): m(orgin.m), n(orgin.n), data(orgin.data) {}
    //Default destructor is enough


    //non const access class
    non_const_interface operator[](size_t i) {
        auto a = data.begin() + i*n;
        return non_const_interface(a);
    }
    //const access class
    const_interface operator[](size_t i) const {
        auto a = data.cbegin() + i*n;
        return const_interface(a);
    }

    //attribute getters follows

    const size_t& dim_m() const {
        return m;
    }

    const size_t& dim_n() const {
        return n;
    }
    //implementation of operator+, this method throws std::logic_error if passed wrong matrixes

    inline friend matrix operator+(const matrix& fm,const matrix& sm) {
        if (fm.m!=sm.m || fm.n!=sm.n)  throw std::logic_error("Adding matrixes with diffrent dimensions");
        matrix tmp(fm.m,sm.n);
        for (int i=0; i<fm.m; ++i) {
            for (int j=0; j<sm.n; ++j) {
                tmp[i][j]=fm[i][j]+sm[i][j];
            }
        }
        return tmp;
    }

    inline friend std::ostream& operator<<(std::ostream& out, const matrix& m) {
        out<<"m= "<<m.m<<", n= "<<m.n<<"\n";
        for (int i = 0 ; i<m.m; ++i){
            out<<"[ ";
            for (int j=0; j<m.n-1; ++j){
                out<<m[i][j]<<" , ";
            }
            out<<m[i][m.n-1]<<" ]\n";
        }
        out<<""; // don't understand it at all! (without this line program returns segmentation fault!)
    }

private:
    // constructor for "copy" creation
    matrix(const size_t& a, const size_t& b, const std::vector<int>& init): m(a), n(b), data(init) {}
    //data storage
    std::vector<T> data;
    //dimensions variables
    std::size_t m,n;
};
#endif //MATRIX_MATRIX_H
