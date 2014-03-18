#ifndef __H_NODE__H__
#define __H_NODE__H__

#include <vector>
#include <map>

namespace h_ {

/*******************************************************************************
 *
 *               Typedefs that'll make life a little easier.
 *
 ******************************************************************************/
 
typedef std::vector<unsigned char> string;
typedef std::vector< bool > bitstring;
typedef std::pair< bitstring::iterator, unsigned char > conpair;

//
// FIXME: h_::error needs to be defined
//
class error : public std::exception
{
    
};

/*******************************************************************************
 *
 *        h_::node - a node in the huffman binary tree, holds a byte value, 
 *        and a weight for that value. Can be a branch or a leaf. Encodes
 *        recursively with other attached nodes.
 *
 ******************************************************************************/
class node
{
private:
    //
    // Constructor defines a leaf.
    //
    node( unsigned char b, unsigned int w ) : weight_( w ), byte( b ),
                                              leaf( true ), left( NULL ),
                                              right( NULL )
                                              { };
    //
    // Constructor defines a branch.
    //
    node( node *l, node *r ) throw( error ) : weight_( 0 ), byte( 0 ),
                                              leaf( false )
    {
        if( l == NULL || r == NULL ) throw error( );
        
        if( l->weight_ > r->weight_ )
        {
            right = l;
            left = r;
        }
        else
        {
            left = l;
            right = r;
        }
        
        weight_ = ( l->weight_ + r->weight_ );
    }
    //
    // Destructor it will delete all children!
    //
   ~node( )
    {
        if( left != NULL ) delete left;
        if( right!= NULL ) delete right;
    }
    void add( node *n );
    bitstring encode( unsigned char b );
    conpair decode( bitstring::iterator cur );
    
private:
    unsigned int weight_;
    unsigned char byte;
    bool leaf;
    node *left;
    node *right;
    friend class encoder;
};
}
#endif // __H_NODE_H__

