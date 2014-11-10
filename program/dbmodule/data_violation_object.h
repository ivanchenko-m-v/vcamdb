///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 09-11-2014
///		Date update	: 10-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_VIOLATION_OBJECT_H__
#define __DATA_VIOLATION_OBJECT_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_violation_object
/// ############################################################################
    class data_violation_object
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_violation_object( )
         { }

        virtual ~data_violation_object( )
        { }
    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_object( )
        virtual int id_object( ) const = 0;

    /// ------------------------------------------------------------------------
    ///	okrug
        virtual const QString& okrug( ) const = 0;

    /// ------------------------------------------------------------------------
    ///	district
        virtual const QString& district( ) const = 0;

    /// ------------------------------------------------------------------------
    ///	prefekture
        virtual const QString& prefekture( ) const = 0;

    /// ------------------------------------------------------------------------
    ///	object_name
        virtual const QString& object_name( ) const = 0;

    /// ------------------------------------------------------------------------
    ///	to_string
        virtual QString to_string( ) const = 0;

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_violation_object& operator=( const data_violation_object &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:

    };//class data_violation_object
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_violation_object_collection
/// ############################################################################
    class data_violation_object_collection
    {
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_violation_object_collection( const data_violation_object_collection &rhs );
    public:
    /// ------------------------------------------------------------------------
        data_violation_object_collection( ) :
            _data( 0 )
        { }
    /// ------------------------------------------------------------------------
        virtual ~data_violation_object_collection( )
        { this->free( ); }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    public:
    /// ------------------------------------------------------------------------
        int size( ) const
        {
            if( !this->_data )
            {
                return 0;
            }
            return this->_data->size( );
        }

    /// ------------------------------------------------------------------------
        void free_data_pointer( )
        {
            if( !this->_data )
            {
                return;
            }
            //free pointer to list
            //but save pointers on list elements
            delete _data;
            this->_data = 0;
        }

    /// ------------------------------------------------------------------------
        void free( )
        {
            if( !this->_data )
            {
                return;
            }
            while( this->_data->size( ) )
            {
                //get last element
                data_violation_object *r = this->_data->last( );
                //remove last element from list
                this->_data->removeLast( );
                //delete last element
                delete r;
            }
            delete _data;

            this->_data = 0;
        }

    /// ------------------------------------------------------------------------
        void append( data_violation_object *r )
        {
            if( !this->_data )
            {
                this->_data = new QList<data_violation_object *>;
            }
            this->_data->append( r );
        }

        /// ------------------------------------------------------------------------
        const data_violation_object* find( const int id_object )
        {
            data_violation_object *pvo = 0;
            iterator it = this->begin( );
            for( ; it < this->end( ); ++it )
            {
                data_violation_object *vobj = *it;

                if( !vobj ) continue;

                if( vobj->id_object( ) == id_object )
                {
                    pvo = vobj;
                    break;
                }
            }

            return pvo;
        }

    /// ------------------------------------------------------------------------
        QList<data_violation_object *>* list( )
        { return this->_data; }

    /// ------------------------------------------------------------------------
        typedef QList<data_violation_object *>::iterator iterator;
    /// ------------------------------------------------------------------------
        iterator begin( )
        {
            return this->_data->begin( );
        }

    /// ------------------------------------------------------------------------
        iterator end( )
        {
            return this->_data->end( );
        }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_violation_object_collection& operator=(
                                        const data_violation_object_collection &rhs
                                         );
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QList<data_violation_object *>	*_data;

    };//class data_violation_object_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_VIOLATION_OBJECT_H__
