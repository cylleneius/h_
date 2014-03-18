#include "h_node.h"
    //
    // add( ) method: adds another node to tree. When called on root, it will
    // generate an appropriate tree.
    //
void h_::node::add( node *n )
{
    //
    // We construct the tree here! This all assumes n will be increasingly
    // small. But, I think it'll construct the tree correctly regardless :D
    //
    if( leaf )
    {
        //
        // If we're a leaf, we gotta make room. We favor right being heavy.
        //
        if( weight_ > n->weight_ )
        {
            left = n;
            right = new node( byte, weight_ );
        }
        else
        {
            right = n;
            left = new node( byte, weight_ );
        }
        leaf = false;
        byte = '0';
        weight_ = right->weight_ + left->weight_;
    }
    else
    {
        //
        // If we're a branch, we see if the new node is larger than the two
        // ends. If it is, we make the new node it's own end.
        //
        if( right->weight_ < n->weight_  &&
             left->weight_ < n->weight_ )
        {
            node *branch = new node( left, right );
            if( branch->weight_ > n->weight_ )
            {
                left  = n;
                right = branch;
            }
            else
            {
                right = n;
                left = branch;
            }
            weight_ = right->weight_ + left->weight_;
        }
        //
        // Otherwise, we see which end is smaller, and add the new node to 
        // that one.
        //
        else
        {
            if( right->weight_ < n->weight_ ) right->add( n );
            else left->add( n );
            //
            // Just to correct which side is larger.
            //
            if( right->weight_ < left->weight_ )
            {
                node *t = left;
                left = right;
                right = t;
            }
            weight_ = right->weight_ + left->weight_;
        }
    }
}
    //
    // Step through tree and return the encoded bitstring
    //
h_::bitstring h_::node::encode( unsigned char b )
{
    bitstring r;
    if( !leaf )
    {
        if( left == NULL && right == NULL ) throw error( );
        //
        // Right is larger, so we go that way first.
        //
        r = right->encode( b );
        if( !r.empty( ) )
        {
            r.push_back( false );
            return r;
        }
        r = left->encode( b );
        if( !r.empty( ) )
        {
            r.push_back( true );
            return r;
        }
    }
    else
    {
        if( b == byte )
        {
            //
            // Although ultimately ignored, this'll tell the caller that
            // we've hit the mark
            //
            r.push_back( true );
            return r;
        }
        else return r;
    }
    return r;
}
    //
    // Step through a bitstring until we hit a leaf, return leaf and iterator
    // in h_conpair.
    //
h_::conpair h_::node::decode( bitstring::iterator cur )
{
    if( !leaf )
    {
        if( left == NULL || right == NULL ) throw error( );
        //
        // A set bit (true) is left.
        //
        if( *cur == true )
        {
            cur++;
            return left->decode( cur );
        }
        //
        // And an unset bit (false) is right.
        //
        else
        {
            cur++;
            return right->decode( cur );
        }
    }
    else
    {
        //
        // We're a leaf, so return position iterator and byte we're holding.
        //
        return make_pair( cur, byte );
    }
}
