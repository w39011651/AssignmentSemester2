// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

const int maxSize = 200;

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
      mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
      nodePtr current = myData.myHead;
      for (size_t i = 0; i < count; i++) {
          current->next = new node;
          //new node initialized
          current->next->prev = current;
          current->next->next = myData.myHead;
          current->myVal = Ty();
          //
          current = current->next;
          myData.mySize++;
      }
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   list( const list &right )
      : myData()
   {
       myData.myHead = new node;
       myData.myHead->myVal = right.myData.myHead->myVal;
       myData.myHead->prev = myData.myHead->next = myData.myHead;
       //myData.myHead initialized
       nodePtr LeftCurrent = myData.myHead, RightCurrent=right.myData.myHead;
       for (size_t i = 0; i < right.myData.mySize; i++) {
           LeftCurrent->next = new node;
           //pointer 
           LeftCurrent->next->prev = LeftCurrent;
           LeftCurrent->next->next = myData.myHead;
           //
           LeftCurrent = LeftCurrent->next;
           RightCurrent = RightCurrent->next;
           myData.mySize++;
           LeftCurrent->myVal = RightCurrent->myVal;
       }

   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   list& operator=( const list &right )
   {
      if( this != &right )
          if (myData.mySize < right.myData.mySize) {
              nodePtr current = myData.myHead->prev;//last one
              for (; myData.mySize < right.myData.mySize; myData.mySize++) {
                  current->next = new node;
                  current->next->prev = current;
                  current->next->next = myData.myHead;
                  current->next->myVal = Ty();
                  //
                  current = current->next;
              }
          }
      nodePtr LeftCurrent = myData.myHead->next, RightCurrent=right.myData.myHead->next;
      for (; RightCurrent != right.myData.myHead;) 
      {
          LeftCurrent->myVal = RightCurrent->myVal;
          //simulate iterator
          LeftCurrent = LeftCurrent->next;
          RightCurrent = RightCurrent->next;
      }
      LeftCurrent->prev->next = myData.myHead;
      myData.mySize = right.myData.mySize;
      return *this;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return myData.myHead->next;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return myData.myHead;
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // The container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the list size by the amount of elements inserted.
   // Returns an iterator that points to the newly inserted element.
   iterator insert( const_iterator where, const Ty &val ) // insert val at where
   {
       nodePtr append = new node;
       nodePtr front = where->prev;
       append->prev = front;
       append->next = front->next;
       append->myVal = val;
       front->next = append;
       front->next->prev = append;
       myData.mySize++;
       return append;
   }

   // Removes from the list container the element at the specified position.
   // This effectively reduces the container size one, which is destroyed.
   // Returns an iterator pointing to the element that followed the element erased.
   // This is the container end if the operation erased the last element in the sequence.
   iterator erase( const_iterator where )
   {
       nodePtr front = where->prev, after=where->next;
       front = after;
       after = front;
       delete where;
       myData.mySize--;
       return myData.myHead;
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          nodePtr current = myData.myHead->prev, pos=current;
          for (current; current != myData.myHead;pos=current ) {
              erase(pos);
          }
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
    size_t lhsize = left.size(), rhsize = right.size();
    if ( lhsize != rhsize ) {
        return false;
    }
    else {
        typename list<Ty>::iterator rLit = left.end()->prev;
        typename list<Ty>::iterator rRit = right.end()->prev;
        for (; rLit != left.end();) {
            if (rLit != rRit) {
                return false;
            }
            rLit = rLit->prev;
            rRit = rRit->prev;
        }
        return true;
    }
}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
{
   return !( left == right );
}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   // constructor; construct a zero HugeInteger with size n
   HugeInteger( unsigned int n = 0 )
      : integer( ( n == 0 ) ? 1 : n )
   {
   }

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy )
      : integer( integerToCopy.integer )
   {
   }

   // destructor; destroys the HugeInteger
   ~HugeInteger()
   {
   }

   // overloaded assignment operator;
   // return avoids: ( a1 = a2 ) = a3
   const HugeInteger& operator=( const HugeInteger &right )
   {
      if( &right != this ) // avoid self-assignment
         integer = right.integer;

      return *this; // enables x = y = z, for example
   }

   // function that tests if two HugeIntegers are equal
   bool operator==( const HugeInteger &right )
   {
      return ( integer == right.integer );
   } // end function operator==

   // function that tests if one HugeInteger is less than another
   bool operator<( HugeInteger &right )
   {
       typename T::iterator lit = integer.end()->prev;
       typename T::iterator rit = right.integer.end()->prev;
       size_t lhs = size(), rhs = right.size();
       if (lhs > rhs) {
           return false;
       }
       else if (lhs < rhs) {
           return true;
       } 
       else {
           for (;lit!=integer.end();) {
               if (lit->myVal < rit->myVal) {
                   return true;
               }
               else if (lit->myVal > rit->myVal) {
                   return false;
               }
               else {
                   lit = lit->prev;
                   rit = rit->prev;
               }
           }
       }
   } // end function operator<

   // function that tests if one HugeInteger is less than or equal to another
   bool operator<=( HugeInteger &right )
   {
      return ( *this == right || *this < right );
   }

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 )
   {
      HugeInteger zero;
      if( *this == op2 )
         return zero;

      HugeInteger difference( *this );
      typename T::iterator it1 = integer.begin();
      typename T::const_iterator it2 = op2.integer.begin();
      typename T::iterator it3 = difference.integer.begin();
      //calculate
      for (; it2 != op2.integer.end();) {
          if (it3->myVal < it2->myVal) {
              typename T::iterator itTemp = it3->next;
              for (; itTemp->myVal != 0; itTemp = itTemp->next) {
                  if (itTemp->myVal > 0) {
                      itTemp->myVal -= 1;
                      break;
                  }
                  else {
                      itTemp->myVal += 9;
                  }
              }
              it3->myVal += 10;
          }
          it3->myVal -= it2->myVal;
          it3 = it3->next;
          it2 = it2->next;
      }
      //check leading zero
      it3 = difference.integer.end()->prev;
      while (true) {
          if (it3->myVal == 0) {
              typename T::iterator itTemp = it3->prev;
              difference.integer.erase(it3);
              it3 = itTemp;
          }
          else {
              break;
          }
      }
      if( difference.leadingZero() )
         cout << "difference has a leading zero!\n";

      return difference;
   }

   // subtraction assignment operator; HugeInteger -= HugeInteger
   void operator-=( HugeInteger &op2 )
   {
      *this = *this - op2;
   }

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger &op2 )
   {
      HugeInteger zero;
      if( isZero() || op2.isZero() )
         return zero;

      HugeInteger product( integer.size() + op2.integer.size() );
      typename T::iterator productIt = product.integer.begin();
      typename T::iterator it1 = integer.begin(), end1=integer.end();
      typename T::iterator it2 = op2.integer.begin(), end2=op2.integer.end();
      for (; it1 != end1; it1 = it1->next) {
          for (; it2 != end2; it2 = it2->next) {
              
          }//how to make the iterator of product??
      }

      if( product.leadingZero() )
         cout << "product has a leading zero!\n";

      return product;
   }

   // multiplication assignment operator; HugeInteger *= HugeInteger
   void operator*=( HugeInteger &op2 )
   {
      *this = *this * op2;
   }

   // division operator; HugeInteger / HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator/( HugeInteger &op2 )
   {
      HugeInteger zero;
      if( *this < op2 )
         return zero;

      HugeInteger quotient;

      return quotient;
   } // end function operator/

   // modulus operator; HugeInteger % HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator%( HugeInteger &op2 )
   {
      return *this - ( ( *this / op2 ) * op2 );
   }

   // overloaded prefix increment operator 
   HugeInteger& operator++()
   {
      helpIncrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix increment operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator++( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpIncrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // overloaded prefix decrement operator 
   HugeInteger& operator--()
   {
      helpDecrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix decrement operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator--( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpDecrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // convert an integer into a HugeInteger
   void convert( const value_type &number )
   {
      integer.erase( integer.end()->prev );
      for( value_type i = number; i > 0; i /= 10 )
         integer.insert( integer.end(), i % 10 );
   }

   // compute base raised to the power of expon
   void power( HugeInteger &base, const value_type &expon )
   {
      integer.begin()->myVal = 1;
      for( value_type i = 0; i < expon; ++i )
      {
         *this *= base;
         if( integer.size() > maxSize - base.integer.size() )
            break;
      }
   }

   size_type size()
   {
      return integer.size();
   }

   // return true if and only if all digits are zero
   bool isZero()
   {
      typename T::iterator it = integer.begin();
      for( ; it != integer.end(); it = it->next )
         if( it->myVal != 0 )
            return false;

      return true;
   }

   // return true if and only if the leftmost digit is zero
   bool leadingZero()
   {
      return ( integer.size() > 1 && integer.back() == 0 );
   }

private:
   T integer;

   // function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
   void divideByTen()
   {
      typename T::iterator it = integer.begin()->next;
      for( ; it != integer.end(); it = it->next )
         ( it->prev )->myVal = it->myVal;
      integer.erase( integer.end()->prev );
   }

   // function to help increment the integer
   void helpIncrement()
   {
      typename T::iterator it = integer.begin();
      ( it->myVal )++;
      typename T::iterator it2 = it;
      for( it2 = it2->next; it2 != integer.end(); it = it->next, it2 = it2->next )
         if( it->myVal == 10 )
         {
            it->myVal = 0;
            ( it2->myVal )++;
         }

      if( ( it->myVal ) == 10 )
      {
         it->myVal = 0;
         integer.insert( integer.end(), 1 );
      }
   }

   // function to help decrement the integer
   void helpDecrement()
   {
      typename T::iterator it = integer.begin();
      for( ; it->myVal == 0; it = it->next )
         it->myVal = 9;

      ( it->myVal )--;

      if( !isZero() && integer.back() == 0 )
         integer.erase( integer.end()->prev );
   }
}; // end class HugeInteger


// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end()->prev;
   for( ; it != hugeInteger.integer.begin()->prev; it = it->prev )
      if( it->myVal < 10 )
         output << it->myVal;

   return output; // enables cout << x << y;
}


template< typename T1, typename T2 >
void solution2( T2 t, T2 a, T2 b )
{
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInteger< T1 > base;
         base.convert( t ); // put all digits of t into base

         HugeInteger< T1 > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< T1 > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               HugeInteger< T1 > quotient = dividend / divisor;
               HugeInteger< T1 > remainder = dividend % divisor;

               if( quotient.leadingZero() )
                  cout << "quotient has a leading zero!\n";

               if( remainder.leadingZero() )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && remainder.isZero() )
                  cout << quotient << endl;
               else
                  cout << "is not an integer with less than 100 digits.\n";
            }
         }
      }
   }
}

template< typename T >
void solution1()
{
   T t = T(), a = T(), b = T();
   solution2< list< T > >( t, a, b );
}

int main()
{
   // execute the following 6 instructions one by one, each of them should get an AC
   solution1< int >();
//   solution1< unsigned int >();
//   solution1< long int >();
//   solution1< unsigned long int >();
//   solution1< long long int >();
//   solution1< unsigned long long int >();

   system( "pause" );
   //TEST GITHUB PUSH
}