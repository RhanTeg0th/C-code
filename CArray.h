//---------------------------------------------------------------------
// example of a template Array Class using dynamic allocation
// by Paul Bladek
// compiled using MS Visual C++.NET 2003
// v1.0  completed May 20, 2003
// v1.01 completed November 30, 2005
//---------------------------------------------------------------------

#ifndef CARRAY_H
#define CARRAY_H

#include <iostream>
#include <exception>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include "assert.h"
using namespace std;

typedef unsigned int u_int;


	template <class T>
	class CArray
	{
		public:
			// constructors
			
			CArray(u_int size=10, T element = T(0));
			CArray(u_int &size, T element = T(0));
			CArray(CArray<T>& arg);

			
			~CArray() { if(m_array != NULL) free(m_array); }
			u_int getSize()const { return m_size; }
			
			void print(ostream& sout, char delimiter = ' ') const;


			
			// operators
			
			T& operator[](u_int index);
			void operator*=(T scalar);
			void operator*=(CArray<T>& arg);			
			void operator+=(CArray<T>& arg);			
			void operator &(T scalar);
			void operator !();
			CArray<T> operator*(T scalar);
			CArray<T> operator*(CArray<T>& arg);
			CArray<T> operator=(const CArray<T>& arg);
			CArray<T> operator&(CArray<T>& arg);
			CArray<T> operator+(CArray<T>& arg);
			
			
			
			
						
		private: // properties
			T* m_array;
			unsigned int m_size;
			void set_array(u_int index, T element){ this->m_array[index]=element;}
			
			
			
			
			
	};

	template <class T>
	void operator<<(ostream& sout,const CArray<T> &arrray);

	template <class T>
	CArray<T> PLUS(CArray<T>& array);


	
//---------------------------------------------------------------------
// constructors
//---------------------------------------------------------------------
	template <class T>
	CArray<T>::CArray(u_int size, T element)
		: m_array(NULL), m_size(size)
	{
		
		if(size > 0)
			m_array = new T[size];
		for(u_int  i = 0; i < size; i++){
			m_array[i] = element;
		   }
		

	}

	template <class T>
	CArray<T>::CArray(u_int &size, T element)
		: m_array(NULL)
	{

		assert(size>0);
		
		m_size = size;
		m_array = new T[size];
		for(u_int i = 0; i < m_size ; i++){
		    m_array[i] = element;
		}

	}

	
	


//---------------------------------------------------------------------
// copy constructor
//---------------------------------------------------------------------
	template <class T>
    CArray<T>:: CArray(CArray<T>& arg) 
    
   {

	 u_int size = arg.getSize();
     assert(size>0);

	 m_array = new T[size];
	 m_size  = size;

	 for(unsigned int i =0; i < size ; i++){

		 m_array[i] = arg[i];

	 }

	  
  }
//---------------------------------------------------------------------
// print()	prints the elements of the array to sout
//---------------------------------------------------------------------
	template <class T>
	void CArray<T>::print(ostream& sout, char delimiter) const
	{
		for(u_int i = 0; i < m_size; i++)
			sout << m_array[i] << delimiter;
		sout << endl;
	} 

//---------------------------------------------------------------------
// operator=     deep copy
//---------------------------------------------------------------------
	template <class T>
	CArray<T> CArray<T>::operator=(const CArray<T>& array)
	{
		if(this != &array)  // don't let it copy over itself
		{
			m_size = array.m_size;
			if(m_array)
				delete[] m_array;
			m_array = NULL;
			if(m_size > 0)
				m_array = new T[m_size];
			for(u_int i = 0; i < m_size; i++)
				m_array[i] = array.m_array[i];
		}
		return *this;
	}

//---------------------------------------------------------------------
// operator[]    modify individual array members
//---------------------------------------------------------------------
	template <class T>
	T& CArray<T>::operator[](u_int index)
	{
		if(index >= m_size)
		{
			throw exception("Index out-of-bounds");

		}else{
		  
		 return m_array[index];

		}
	}


//---------------------------------------------------------------------
// operator*   scalar multiplication--multiplies each element by scalar
//---------------------------------------------------------------------
	template <class T>
	CArray<T> CArray<T>::operator*(T scalar)
	{	
		CArray<T> temp(*this);
		for(u_int i = 0; i < m_size; i++){
			temp[i] = m_array[i] * scalar;
		}

		return temp;
		
	}

	template <class T>
	CArray<T> CArray<T>::operator*(CArray<T>& arg)
	{	

		u_int s = this->getSize();
		u_int t = arg.getSize();
		assert(s==t);

		CArray<T> temp0(*this);

		for(u_int i = 0; i < s; i++){

			temp0[i] = m_array[i]*arg[i];

		}


		return C;

	}

//---------------------------------------------------------------------
// operator*=    scalar multiplication and assignment
//---------------------------------------------------------------------
	template <class T>
	void CArray<T>::operator*=(T scalar) 
	{
		 
		 for(u_int i = 0; i < m_size ; i++){
		        m_array[i]=m_array[i]*scalar;
		      
		 }

		  
	}

	template <class T>
	void CArray<T>::operator*=(CArray<T>& arg)
	{

		for(u_int i = 0; i < m_size; i++){

			m_array[i] = m_array[i]*arg[i];

		}


	}
				
//---------------------------------------------------------------------
// operator&    scalar addition  and assignment
//---------------------------------------------------------------------


   template <class T>
   void CArray<T>::operator&(T scalar)
   {


	   for(u_int i = 0; i < m_size ; i++){
		        m_array[i]=m_array[i]+scalar;
		      
		 }


   }
//---------------------------------------------------------------------
// operator+   Adding an additional array to the end of another
//---------------------------------------------------------------------

	

	template <class T>
	void CArray<T>::operator+=(CArray<T>& arg)
	{
	
	   CArray A(*this);
	   CArray B(arg);
	   
	   u_int size = this->m_size;
	   u_int asize = arg.getSize();

	   delete[] this->m_array;

	   this->m_size = size + asize;
	   this->m_array = new T[size+asize];

	   for(u_int i = 0; i < size; i++){

		   this->m_array[i] = A[i];

	   }

	   for(u_int j = 0; j < asize; j++){

		   this->m_array[size+j] = B[j];

	   }
	
	   
	
	
	}


//---------------------------------------------------------------------
// operator+   Sum of 2 arrays   
//---------------------------------------------------------------------

	template <class T>
	CArray<T> CArray<T>::operator+(CArray<T>& arg){

		u_int size  = this->getSize();
		u_int asize = arg.getSize();
		
		CArray<T> A(arg);
		CArray<T> Sum(*this);


		Sum+=arg;

	   

	   for(u_int i = 0; i < asize; i++){

		   Sum.set_array(size+i,A[i]);

	   }
	
	   return Sum;


	}

//---------------------------------------------------------------------
// operator !()  reverses the order of array elements


//  Index[0, m_size-1] -> Index[m_size-1,0]
//---------------------------------------------------------------------




	template <class T>
	void  CArray<T>:: operator !(void)

	{

      CArray<T> temp(*this);

	  for(u_int i = 0; i < m_size; i++){

		  temp[i] = m_array[i];
		 
	  }
	  
	  cout << endl;
	    
	  u_int s = m_size-1;

	  for(u_int j = 0; j < m_size ; j++){
		 
		      
		m_array[j] = temp[s-j];  
		  
		  	  	  
	  
	  }

	  

	}

	
//---------------------------------------------------------------------
// operator<<    outputs array to sout


//  m_size-(i+1) = i .......m_
//---------------------------------------------------------------------
	template <class T>
	void operator<<(ostream& sout, const CArray<T> &arrray)
	{
		arrray.print(sout);
		
	}	




#endif