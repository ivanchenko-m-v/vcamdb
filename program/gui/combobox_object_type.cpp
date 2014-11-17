/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 02-11-2014
///		Date update	: 17-11-2014
///		Comment		:
/// ============================================================================
#include "combobox_object_type.h"

#include "application.h"
#include "business_logic.h"

#include "data_model_object_type.h"
#include "data_adapter_object_type.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_object_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_object_type( )
    /// ------------------------------------------------------------------------
    combobox_object_type::combobox_object_type(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_object_type( )
    /// ------------------------------------------------------------------------
    combobox_object_type::~combobox_object_type( )
    {

    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	object_type( )
    /// ------------------------------------------------------------------------
    QString combobox_object_type::object_type( )
    {
        if( this->currentIndex( ) == -1 )
        {
            return QString( "" );
        }
        return this->itemData( this->currentIndex( ) ).toString( );
    }

    /// ------------------------------------------------------------------------
    ///	object_type( )
    /// ------------------------------------------------------------------------
    void combobox_object_type::object_type( const QString &s_type )
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
    void combobox_object_type::initialize( )
    {
        data_model_object_type *model = application::the_business_logic( ).
                                                            model_object_type( );
        if( !model )
        {
            return;
        }
        const data_object_type_list& list = model->list( );
        if( !list.size() )
        {
            return;
        }

        this->addItem( "", "" );
        for( int i=0; i<list.size( );++i)
        {
            const data_object_type *rec = list.at( i );
            this->addItem( rec->object_type( ), rec->object_type( ) );
        }
    }

}//namespace vcamdb
