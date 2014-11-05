/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 04-11-2014
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

#include "application.h"
#include "business_logic.h"

#include "data_model_cam_selection.h"
#include "data_model_violation.h"
#include "data_model_camera.h"
#include "data_model_camera_object.h"
#include "data_model_object_type.h"
#include "data_model_violation_type.h"

#include "data_adapter_object_type.h"
#include "data_adapter_camera.h"
#include "data_adapter_violation_type.h"

namespace vcamdb
{

/// ############################################################################
///			class business_logic
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
    /// ------------------------------------------------------------------------
    ///	free_memory( )
    /// ------------------------------------------------------------------------
    void business_logic::free_memory( )
    {
        if( this->_model_cam_selection )
        {
            delete _model_cam_selection;
        }
        if( this->_model_violation )
        {
            delete _model_violation;
        }
        if( this->_model_camera )
        {
            delete _model_camera;
        }
        if( this->_model_camera_object )
        {
            delete _model_camera_object;
        }
        if( this->_model_object_type )
        {
            delete _model_object_type;
        }
        if( this->_model_violation_type )
        {
            delete _model_violation_type;
        }
    }

	/// ------------------------------------------------------------------------
	///	init( )
    /// ------------------------------------------------------------------------
	void business_logic::init( )
	{
		try
		{
            //this->init_db_path( );
            this->init_data_models( );
		}
		catch( std::exception &ex )
		{
			QString s_msg(
							"business_logic::init( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
			QString s_msg(
						"business_logic::init( )"
						":\n\t unknown error while initialize business logic"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
	}
	/// ------------------------------------------------------------------------
	///	exit( )
    /// ------------------------------------------------------------------------
	void business_logic::exit( )
	{
        this->free_memory( );

		qDebug( ) << "correctly exiting business logic";
	}

    /// ------------------------------------------------------------------------
    ///	init_data_models( )
    /// ------------------------------------------------------------------------
    void business_logic::init_data_models( )
    {
        this->init_model_cam_selection( );

        this->init_model_violation( );

        this->init_model_camera( );

        this->init_model_camera_object( );

        this->init_model_object_type( );

        this->init_model_violation_type( );
    }

    /// ------------------------------------------------------------------------
    ///	init_model_cam_selection( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_cam_selection( )
    {
        this->_model_cam_selection = new data_model_cam_selection;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_violation( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_violation( )
    {
        this->_model_violation = new data_model_violation;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_camera( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_camera( )
    {
        this->_model_camera = new data_model_camera;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_camera_object( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_camera_object( )
    {
        this->_model_camera_object = new data_model_camera_object;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_object_type( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_object_type( )
    {
        this->_model_object_type = new data_model_object_type;
        this->object_type_select( );
    }

    /// ------------------------------------------------------------------------
    ///	init_model_violation_type( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_violation_type( )
    {
        this->_model_violation_type = new data_model_violation_type;
        this->violation_type_select( );
    }

///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///
/// BLOCK object_type
///
///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /// ------------------------------------------------------------------------
    ///	object_type_select( )
    /// ------------------------------------------------------------------------
    void business_logic::object_type_select( )
    {
        data_object_type_collection *p_coll = 0;
        try
        {
            data_adapter_object_type adap;
            //select data
            p_coll = adap.select( );
            //refresh data model
            this->_model_object_type->refresh( p_coll );
        }
        catch( std::exception &ex )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                            "business_logic::object_type_select( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                        "business_logic::object_type_select( )"
                        ":\n\t unknown error while OBJECT_TYPE select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///
/// BLOCK violation_type
///
///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /// ------------------------------------------------------------------------
    ///	violation_type_select( )
    /// ------------------------------------------------------------------------
    void business_logic::violation_type_select( )
    {
        data_violation_type_collection *p_coll = 0;
        try
        {
            data_adapter_violation_type adap;
            //select data
            p_coll = adap.select( );
            //refresh data model
            this->_model_violation_type->refresh( p_coll );
        }
        catch( std::exception &ex )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                            "business_logic::violation_type_select( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                        "business_logic::violation_type_select( )"
                        ":\n\t unknown error while VIOLATION_TYPE select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///
/// BLOCK camera
///
///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /// ------------------------------------------------------------------------
    ///	camera_select( )
    /// ------------------------------------------------------------------------
    data_camera_collection* business_logic::camera_select( const QString &s_filter )
    {
        const int MIN_FILTER_LENGTH = 5;
        data_camera_collection *p_coll = 0;

        if( s_filter.length( ) < MIN_FILTER_LENGTH )
        {
            return p_coll;
        }

        try
        {
            data_adapter_camera adap;
            //select data
            p_coll = adap.select( s_filter );
        }
        catch( std::exception &ex )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                            "business_logic::camera_select( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                        "business_logic::camera_select( )"
                        ":\n\t unknown error while CAMERA select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        return p_coll;
    }

/// ############################################################################

}//namespace vcamdb
