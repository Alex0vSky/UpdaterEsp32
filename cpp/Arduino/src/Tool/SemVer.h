// src/Tool/SemVer.h - wrapper SemVer string
// @insp https://www.geeksforgeeks.org/compare-two-version-numbers/
// @insp SO/how-to-best-overload-operator-but-only-write-one-or-two-comparison-fun
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool {
namespace detail {
template <typename T>
struct implement_relational_operators {
	friend bool operator<=(const T & a,const T & b){ return a < b || a == b; }
	friend bool operator>(const T &  a, const T & b){ return !(a <= b); }
	friend bool operator!=(const T &  a, const T & b){ return !(a == b); }
	friend bool operator>=(const T &  a, const T & b){ return !(a < b); }
};
} // namespace detail
class SemVer : public detail::implement_relational_operators< SemVer > {
	using string = std::string;
	struct Private{};
	const String m_semVer;

	// Method to compare two versions. 
	// Returns 1 if v2 is smaller, -1 
	// if v1 is smaller, 0 if equal 
	int versionCompare_(String const& v2) const { 
		String const& v1 = m_semVer;
		// vnum stores each numeric 
		// part of version 
		int vnum1 = 0, vnum2 = 0; 

		// loop until both string are 
		// processed 
		for (int i = 0, j = 0; (i < v1.length() 
								|| j < v2.length());) { 
			// storing numeric part of 
			// version 1 in vnum1 
			while (i < v1.length() && v1[i] != '.') { 
				vnum1 = vnum1 * 10 + (v1[i] - '0'); 
				i++; 
			} 

			// storing numeric part of 
			// version 2 in vnum2 
			while (j < v2.length() && v2[j] != '.') { 
				vnum2 = vnum2 * 10 + (v2[j] - '0'); 
				j++; 
			} 

			if (vnum1 > vnum2) 
				return 1; 
			if (vnum2 > vnum1) 
				return -1; 

			// if equal, reset variables and 
			// go for next numeric part 
			vnum1 = vnum2 = 0; 
			i++; 
			j++; 
		} 
		return 0; 
	} 

public:
	SemVer(Private, String semVer) : 
		m_semVer( semVer )
	{}
	typedef std::shared_ptr< SemVer > sptr_t;
	static sptr_t create(String const& semVer) {
		char *begin = const_cast< char *>( semVer.begin( ) );
		if ( 'v' == *begin )
			++begin;
		char *endptr = begin - 1;
		do { 
			strtoul( ++endptr, &endptr, 10 );
			if ( '.' != *endptr ) 
				break;
			strtoul( ++endptr, &endptr, 10 );
			if ( '.' != *endptr ) 
				break;
			strtoul( ++endptr, &endptr, 10 );
			if ( '\0' != *endptr ) 
				break;
			return std::make_shared< SemVer >( Private(), semVer );
		} while ( false );
		return { };
	}

	bool operator < (Tool::SemVer const& rhs) const {
		return versionCompare_( rhs.m_semVer ) < 0;
	}
	bool operator == (Tool::SemVer const& rhs) const {
		return versionCompare_( rhs.m_semVer ) == 0;
	}

};
} // namespace Tool

// Avoid pointer comparison
bool operator < (Tool::SemVer::sptr_t const&, Tool::SemVer::sptr_t const& ) = delete;
bool operator > (Tool::SemVer::sptr_t const&, Tool::SemVer::sptr_t const& ) = delete;
bool operator == (Tool::SemVer::sptr_t const&, Tool::SemVer::sptr_t const& ) = delete;
bool operator != (Tool::SemVer::sptr_t const&, Tool::SemVer::sptr_t const& ) = delete;
bool operator <= (Tool::SemVer::sptr_t const&, Tool::SemVer::sptr_t const& ) = delete;
bool operator >= (Tool::SemVer::sptr_t const&, Tool::SemVer::sptr_t const& ) = delete;
