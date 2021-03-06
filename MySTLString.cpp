#include "MySTLString.h"
#include <cstring>
#include <stdexcept>

// Construct a empty string(zero size and unspecified capacity).
MySTLString::MySTLString():data_(nullptr), length_(0)
{
	
}

// Constructs the string with count copies of character ch.
MySTLString::MySTLString(size_t count, char ch)
{
	length_ = count;
	if (count == 0)
	{	
		data_ = nullptr;
		return;
	}
	else	// when count is not 0
	{
		data_ = new char[length_+1];
		for (size_t i = 0; i < count - 1; ++i)
		{
			data_[i] = ch;
		}
		data_[count - 1] = '\0';
	}
	
}

// Constructs the string with contents initialized 
// with a copy of the null-terminated character string pointed to by s.
// The length of the string is determined by the first null character. 
MySTLString::MySTLString(const char *s)
{
	length_ = strlen(s);
	if (length_ == 0)
	{
		data_ = nullptr;
		return;
	}
	data_ = new char[length_+1];
	strcpy(data_, s);
}

// Copy constructor. 
// Constructs the string with the copy of the contents of other.
MySTLString::MySTLString(const MySTLString &s)
{
	if (s.data_ == nullptr)
	{
		length_ = 0;
		data_ = nullptr;
	}
	else
	{
		length_ = strlen(s.data_);
		data_ = new char[length_+1];
		strcpy(data_, s.data_);
	}
}

// Destructor
// Free data_ pointer memory
MySTLString::~MySTLString()
{
	if (data_ != nullptr)
	{
		delete []data_;
	}
//	std::cout << "length_ = " << length_ << std::endl;	// for test
}



/* Elment access */
// Returns a reference to the character at specified location pos.
// Bounds checking is performed, exception of type std::out_of_range will be thrown on invalid acess
MySTLString::reference MySTLString::at(size_type pos)
{
	if (pos > strlen(data_))
	{
		throw std::out_of_range("pos is cross-border!\n");
	}
	return data_[pos];
}

MySTLString::const_reference MySTLString::at(size_type pos) const
{
	return const_cast<MySTLString*>(this)->at(pos);
}

// Returns reference to the first character
MySTLString::reference MySTLString::front()
{
	if (data_ == nullptr)
	{
		throw std::out_of_range("String is empty!\n");
	}
		return data_[0];
}

MySTLString::const_reference MySTLString::front() const
{
	return const_cast<MySTLString*>(this)->front();
}

// Returns reference to the last character
MySTLString::reference MySTLString::back()
{
	if (data_ == nullptr)
	{
		throw std::out_of_range("String is empty!\n");
	}
	return data_[0];
}

MySTLString::const_reference MySTLString::back() const
{
	return const_cast<MySTLString*>(this)->back();
}

// Returns pointer to the underlying array serving as character storage.
// The pointer is such that the range[data(); data()+strlen(data_)+1) is valid 
// in it correspond to the values stored in the string
MySTLString::CharT* MySTLString::data()
{
	if (data_ == nullptr)
	{
		throw std::out_of_range("String is empty!\n");
	}
	return data_;
}

const MySTLString::CharT* MySTLString::data() const
{
	return const_cast<MySTLString*>(this)->data();
}

// Returns a pointer to null-terminated character array with data equivalent to those stored in the string
// The pointer is such that the arrange [c_str(); c_str() + length_ + 1) is valid and the values in 
// it correspond to the values stored in the string with an additional null character after the last position. 
const MySTLString::CharT* MySTLString::c_str() const
{
	return const_cast<MySTLString*>(this)->data();
}



/* Capacity */
// Checks if the string has no characters
bool MySTLString::empty() const
{
	return length_ == 0;
}

// Returns the number of CharT elements in the string, i.e std::distance(begin(), end())
MySTLString::size_type MySTLString::size() const
{
	return length_;
}

MySTLString::size_type MySTLString::length() const
{
	return length_;
}

// Operator= overloaded
// Replace the contents with a copy of str.
// If *this and str are the same object, this function has no effect
MySTLString& MySTLString::operator=(const MySTLString &s)
{
	// If *this and str are the same object, this function return *this
	if (this == &s)
	{
		return *this;
	}
	if (s.length_ == 0)
	{
		length_ = 0;
		data_ = nullptr;
		return *this;
	}
	char* temp = s.data_;	// copy *s.data_
	delete data_;						// free old memory
	data_ = new char[s.length_+1];			// copy data to data_ member
	strcpy(data_, temp);
	length_ = s.length_;
	return *this;						// return this object
}

// Operator[] overloaded
// Returns a reference to the character at specified location pos. 
// No bounds checking is perfromed.
MySTLString::reference MySTLString::operator[](size_type pos)
{
	return this->at(pos);
}

MySTLString::const_reference MySTLString::operator[](size_type pos) const
{
	return const_cast<MySTLString*>(this)->operator[](pos);
}

// Operator<< overloaded
std::ostream& operator<<(std::ostream& os, MySTLString& myStr)
{
	char* temp = myStr.data_;
	int count = 0;
	int strLen = myStr.size();
	while (count < strLen)
	{
		os << *(temp + count);
		++count;
	}
	
	return os;
}


// Operator== overloaded
bool operator==(const MySTLString& lhs, const MySTLString& rhs)
{
	int lLen = lhs.size();
	int rLen = rhs.size();

	if (lLen == rLen)
	{
		for (size_t i = 0; i < lLen; ++i)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}
	}
	else // lLen != rLen
	{
		return false;
	}

}