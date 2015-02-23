/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-11-2014
///		Date update	: 23-02-2015
///		Comment		:
/// ============================================================================
#include "combobox_violation_type.h"

#include "application.h"
#include "business_logic.h"

//#include "data_model_violation_type.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_violation_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_violation_type( )
    /// ------------------------------------------------------------------------
    combobox_violation_type::combobox_violation_type(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_violation_type( )
    /// ------------------------------------------------------------------------
    combobox_violation_type::~combobox_violation_type( )
    {

    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	violation_type( )
    /// ------------------------------------------------------------------------
    QString combobox_violation_type::violation_type( )
    {
        if( this->currentIndex( ) == -1 )
        {
            return QString( "" );
        }
        return this->itemData( this->currentIndex( ) ).toString( );
    }

    /// ------------------------------------------------------------------------
    ///	violation_type( )
    /// ------------------------------------------------------------------------
    void combobox_violation_type::violation_type(const QString &s_type)
    {
        int index = this->findData( s_type );
        if( index >= 0 )
        {
            this->setCurrentIndex( index );
        }

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_violation_type::initialize( )
    {
        /*
        data_model_violation_type *model = application::the_business_logic( ).
                                                            model_violation_type( );
        if( !model )
        {
            return;
        }
        const data_violation_type_list& list = model->list( );
        if( !list.size() )
        {
            return;
        }

        this->addItem( "", "" );
        for( int i=0; i<list.size( );++i)
        {
            const data_violation_type *rec = list.at( i );
            this->addItem( rec->violation_type( ), rec->violation_type( ) );
        }
*/
        this->setEditable( true );
    }

    /// ------------------------------------------------------------------------
    ///	clear_data( )
    /// ------------------------------------------------------------------------
    void combobox_violation_type::clear_data( )
    {
        //empty text list
        this->clear( );
        //remove previous data
        this->_objects.free( );
    }

    /// ------------------------------------------------------------------------
    ///	refresh( )
    /// ------------------------------------------------------------------------
    void combobox_violation_type::refresh(const QString &object_type )
    {
        this->clear( );

        business_logic &logic = application::the_business_logic( );
        data_violation_type_collection *p_coll = logic.violation_type_select( object_type );
        if( !p_coll )
        {
            return;
        }

        this->addItem( "" );
        data_violation_type_collection::iterator it = p_coll->begin( );
        for( ; it < p_coll->end( ); ++it )
        {
            data_violation_type *vobj = *it;

            if( !vobj ) continue;

            this->addItem( vobj->violation_type( ) );
            this->_objects.append( vobj );
        }

        p_coll->free_data_pointer( );
    }


}//namespace vcamdb
