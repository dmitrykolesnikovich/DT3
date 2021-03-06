#ifndef DT3_COMPONENTGUIDRAWICON
#define DT3_COMPONENTGUIDRAWICON
//==============================================================================
///	
///	File: ComponentGUIDrawIcon.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "ComponentBase.hpp"

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class MaterialResource;
class CameraObject;

//==============================================================================
/// GUI drawing for an image.
//==============================================================================

class ComponentGUIDrawIcon: public ComponentBase {
    public:
        DEFINE_TYPE(ComponentGUIDrawIcon,ComponentBase)
		DEFINE_CREATE_AND_CLONE
		DEFINE_PLUG_NODE

                                    ComponentGUIDrawIcon	(void);	
									ComponentGUIDrawIcon	(const ComponentGUIDrawIcon &rhs);
        ComponentGUIDrawIcon &      operator =              (const ComponentGUIDrawIcon &rhs);	
        virtual                     ~ComponentGUIDrawIcon   (void);
    
        virtual void                archive_read			(Archive *archive);
        virtual void                archive_write		(Archive *archive);
		
	public:
		/// Called to initialize the object
		virtual void				initialize			(void);
        
		/// Returns the component type. This defines which slot the component is
        /// put into on the object.
		/// \return Component type
        virtual ComponentType       getComponentType    (void)  {   return COMPONENT_DRAW;  }

		/// Draw Callback for component
		/// \param camera Camera used for drawing
		/// \param parent_color Color of the parent GUI Object
        void                        draw                (CameraObject* camera, const Color &parent_color);
        
		/// Called when this component is added to the owner. Note that this will
        /// only be called if the owner is added to a world already. If not it 
        /// will be called when it is added to the World.
		/// \param owner Pointer to the owner
		virtual void                addToOwner          (ObjectBase *owner);

		/// Called when this component is removed from its owner.
		virtual void                removeFromOwner     (void);

        /// Defines standard accessors for the material
  		DEFINE_ACCESSORS		(getMaterial, setMaterial, std::shared_ptr<MaterialResource>, _material);

        /// Defines standard accessors for the pressed material
  		DEFINE_ACCESSORS		(getPressedMaterial, setPressedMaterial, std::shared_ptr<MaterialResource>, _pressed_material);

    private:
		Plug<std::shared_ptr<MaterialResource> >         _material;
  		Plug<std::shared_ptr<MaterialResource> >         _pressed_material;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
