#ifndef __H_H__
#define __H_H__

#include <iostream>
#include "h_node.h"

namespace h_
{

/*******************************************************************************
 *
 *     h_::encoder - This class is the one clients need to use.
 *
 ******************************************************************************/

class encoder
{
public:
    
    string encode_inline( string s );
    
    string decode_inline( string s )
    {
        if( s.empty( ) ) return s;
        //
        // Gotta count the characters
        //
        std::map< unsigned char, int > weights;
        std::pair<std::map<unsigned char,int>::iterator,bool> ret;
        string::iterator pos;
        for( pos = s.begin( ); pos < s.end( ); ++pos )
        {
            ret = weights.insert( std::pair<unsigned char,int>(*pos,1) ); 
            if (ret.second == false)
            {
                ret.first->second += 1;
            }
        }
        //
        // Construct binary tree from weight map.
        //
        std::map< unsigned char, int >::iterator x = weights.begin( );
        root = new node( x->first, x->second );
        ++x;
        for( ; x != weights.end( ); ++x )
        {
            root->add( new node( x->first, x->second ) );
        }
        //
        // Encode string from binary tree
        //
        bitstring bs;
        bitstring::reverse_iterator e;
        for( pos = s.begin( ); pos < s.end( ); ++pos )
        {
            bitstring d = root->encode( *pos );
            d.erase( d.begin( ) ); //get rid of true bit
            for( e = d.rbegin( ); e < d.rend( ); ++e )
            {
                std::cout << *e;
            }
            std::cout << " ";
            bs.insert( bs.end( ), d.rbegin( ), d.rend( ) );
        }
        std::cout << std::endl;
        
        bitstring::iterator ef;
        for( ef = bs.begin( ); ef < bs.end( ); ++ef )
        {
            std::cout << *ef;
        }
        std::cout << std::endl;
        
        string ss;
        string::iterator ee;
        for( ef = bs.begin( ); ef < bs.end( ); )
        {
            conpair c = root->decode( ef );
            ef = c.first;
            ss.insert( ss.end( ), c.second );
        }
        for( ee = ss.begin( ); ee < ss.end( ); ++ee )
        {
            std::cout << *ee;
        }
        std::cout << std::endl;
        return s;
    }

private:
    node *root;
};
}
#endif
