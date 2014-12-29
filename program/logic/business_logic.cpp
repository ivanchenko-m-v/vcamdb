/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 29-12-2014
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
#include "data_violation_object.h"
#include "data_adapter_CA.h"
#include "data_adapter_DT.h"
#include "data_adapter_ODH.h"
#include "data_adapter_violation.h"

#include "data_adapter_import_CA.h"
#include "data_adapter_import_ODH.h"
#include "data_adapter_import_DT.h"

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
        this->violation_select( );
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

    /// ------------------------------------------------------------------------
    ///	camera_select_one( )
    /// ------------------------------------------------------------------------
    data_camera* business_logic::camera_select_one(const QString &s_cam_name)
    {
        const int MIN_FILTER_LENGTH = 5;
        data_camera *camera = 0;

        if( s_cam_name.length( ) < MIN_FILTER_LENGTH )
        {
            return camera;
        }

        try
        {
            data_adapter_camera adap;
            //select data
            camera = adap.select_one( s_cam_name );
        }
        catch( std::exception &ex )
        {
            if( camera )
            {
                delete camera;
                camera = 0;
            }
            QString s_msg(
                            "business_logic::camera_select_one( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            if( camera )
            {
                delete camera;
                camera = 0;
            }
            QString s_msg(
                        "business_logic::camera_select_one( )"
                        ":\n\t unknown error while CAMERA select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        return camera;
    }

///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///
/// BLOCK violation_object
///
///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /// ------------------------------------------------------------------------
    ///	violation_object_select( )
    /// ------------------------------------------------------------------------
    data_violation_object_collection*
                  business_logic::violation_object_select(
                                                          const QString &s_type,
                                                          const QString &s_filter
                                                         )
    {
        if( s_type.compare( QString::fromUtf8( "ДТ" ) ) == 0 )
        {
            return this->DT_select( s_filter );
        }
        else if( s_type.compare( QString::fromUtf8( "КП" ) ) == 0 )
        {
            return this->CA_select( s_filter );
        }
        else if( s_type.compare( QString::fromUtf8( "ОДХ" ) ) == 0 )
        {
            return this->ODH_select( s_filter );
        }

        return 0;
    }

    /// ------------------------------------------------------------------------
    ///	CA_select( )
    /// ------------------------------------------------------------------------
    data_violation_object_collection*
                              business_logic::CA_select(const QString &s_filter)
    {
        const int MIN_FILTER_LENGTH = 5;
        data_violation_object_collection *p_coll = 0;

        if( s_filter.length( ) < MIN_FILTER_LENGTH )
        {
            return p_coll;
        }

        try
        {
            data_adapter_CA adap;
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
                            "business_logic::CA_select( )"
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
                        "business_logic::CA_select( )"
                        ":\n\t unknown error while CONTAINER_AREA select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        return p_coll;
    }

    /// ------------------------------------------------------------------------
    ///	DT_select( )
    /// ------------------------------------------------------------------------
    data_violation_object_collection*
                              business_logic::DT_select(const QString &s_filter)
    {
        const int MIN_FILTER_LENGTH = 5;
        data_violation_object_collection *p_coll = 0;

        if( s_filter.length( ) < MIN_FILTER_LENGTH )
        {
            return p_coll;
        }

        try
        {
            data_adapter_DT adap;
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
                            "business_logic::DT_select( )"
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
                        "business_logic::DT_select( )"
                        ":\n\t unknown error while YARD_TERRITORY select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        return p_coll;
    }

    /// ------------------------------------------------------------------------
    ///	ODH_select( )
    /// ------------------------------------------------------------------------
    data_violation_object_collection*
                             business_logic::ODH_select(const QString &s_filter)
    {
        const int MIN_FILTER_LENGTH = 5;
        data_violation_object_collection *p_coll = 0;

        if( s_filter.length( ) < MIN_FILTER_LENGTH )
        {
            return p_coll;
        }

        try
        {
            data_adapter_ODH adap;
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
                            "business_logic::ODH_select( )"
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
                        "business_logic::ODH_select( )"
                        ":\n\t unknown error while ROAD_INFRASTRUCTURE_OBJECT select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        return p_coll;
    }

///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///
/// BLOCK violation
///
///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /// ------------------------------------------------------------------------
    ///	violation_insert( )
    /// ------------------------------------------------------------------------
    void business_logic::violation_insert( const data_violation &record )
    {
        try
        {
            data_adapter_violation adap;
            //insert data
            adap.insert( record );
            //refresh model
            this->violation_select( );
            QMessageBox::information( 0, QObject::tr( "info" ), QObject::tr( "Violation record successfully inserted" ));
        }
        catch( std::exception &ex )
        {
            QString s_msg(
                            "business_logic::violation_insert( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            QString s_msg(
                        "business_logic::violation_insert( )"
                        ":\n\t unknown error while VIOLATION inserting"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

    /// ------------------------------------------------------------------------
    ///	violation_update( )
    /// ------------------------------------------------------------------------
    void business_logic::violation_update( const data_violation &record )
    {
        try
        {
            data_adapter_violation adap;
            //update data
            adap.update( record );
            //update model
            this->_model_violation->update( record );
            QMessageBox::information( 0, QObject::tr( "info" ), QObject::tr( "Violation record successfully updated" ) );
        }
        catch( std::exception &ex )
        {
            QString s_msg(
                            "business_logic::violation_update( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            QString s_msg(
                        "business_logic::violation_update( )"
                        ":\n\t unknown error while VIOLATION updating"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

    /// ------------------------------------------------------------------------
    ///	violation_delete( )
    /// ------------------------------------------------------------------------
    void business_logic::violation_delete( const data_violation &record )
    {
        try
        {
            data_adapter_violation adap;
            //delete data
            adap.del( record );
            //refresh model
            this->violation_select( );
            QMessageBox::information( 0, QObject::tr( "info" ), QObject::tr( "Violation record deleted" ) );
        }
        catch( std::exception &ex )
        {
            QString s_msg(
                            "business_logic::violation_update( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            QString s_msg(
                        "business_logic::violation_update( )"
                        ":\n\t unknown error while VIOLATION updating"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

    /// ------------------------------------------------------------------------
    ///	violation_select( )
    /// ------------------------------------------------------------------------
    void business_logic::violation_select( )
    {
        data_violation_collection *p_coll = 0;

        try
        {
            data_adapter_violation adap;

            QString s_user( application::program_instance( )->user( ) );
            QString s_group( application::program_instance( )->group( ) );
            if( !s_group.compare( "su" ) )
            {
                //for superuser records filtration
                //do not applied
                s_user.clear( );
            }
            else if( s_user.isEmpty( ) )
            {
                //ненастроенный пользователь не должен видеть записи БД
                s_user = "abrakadabra1";
            }
            //select data
            p_coll = adap.select( s_user );
            //refresh data model
            this->_model_violation->refresh( p_coll );
        }
        catch( std::exception &ex )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                            "business_logic::violation_select( )"
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
                        "business_logic::violation_select( )"
                        ":\n\t unknown error while VIOLATION select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///
/// BLOCK import
///
///|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /// ------------------------------------------------------------------------
    ///	ODH_import( const QString &f_file_from )
    /// ------------------------------------------------------------------------
    void business_logic::ODH_import( const QString &f_file_from )
    {
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        try
        {
            data_adapter_import_ODH adap;
            adap.import_file( f_file_from );
            QMessageBox::information( 0, QObject::tr( "info" ), QObject::tr( "ODH import complete" ) );
        }
        catch( std::exception &ex )
        {
            QString s_msg(
                            "business_logic::ODH_import( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            QString s_msg(
                        "business_logic::ODH_import( )"
                        ":\n\t unknown error while importing ODH"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        QApplication::restoreOverrideCursor( );
    }

    /// ------------------------------------------------------------------------
    ///	DT_import( const QString &f_file_from )
    /// ------------------------------------------------------------------------
    void business_logic::DT_import( const QString &f_file_from )
    {
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        try
        {
            data_adapter_import_DT adap;
            adap.import_file( f_file_from );
            QMessageBox::information( 0, QObject::tr( "info" ), QObject::tr( "DT import complete" ) );
        }
        catch( std::exception &ex )
        {
            QString s_msg(
                            "business_logic::DT_import( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            QString s_msg(
                        "business_logic::DT_import( )"
                        ":\n\t unknown error while importing CA"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        QApplication::restoreOverrideCursor( );
    }

    /// ------------------------------------------------------------------------
    ///	CA_import( const QString &f_file_from )
    /// ------------------------------------------------------------------------
    void business_logic::CA_import( const QString &f_file_from )
    {
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        try
        {
            data_adapter_import_CA adap;
            adap.import_file( f_file_from );
            QMessageBox::information( 0, QObject::tr( "info" ), QObject::tr( "CA import complete" ) );
        }
        catch( std::exception &ex )
        {
            QString s_msg(
                            "business_logic::CA_import( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            QString s_msg(
                        "business_logic::CA_import( )"
                        ":\n\t unknown error while importing CA"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        QApplication::restoreOverrideCursor( );
    }

/// ############################################################################

}//namespace vcamdb
