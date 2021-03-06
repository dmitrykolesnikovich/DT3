//==============================================================================
///	
///	File: EdSpriteProperties.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "EdSpriteProperties.hpp"
#include "EdSpritePropertyDefaultField.hpp"
#include "EdSpritePropertyBoolField.hpp"
#include "EdSpritePropertyBitfieldField.hpp"

#include "ArchiveData.hpp"

using namespace DT2;

//==============================================================================
//==============================================================================

EdSpriteProperties::EdSpriteProperties(EdSpriteMainWindow *main_window)
    :   QListWidget     (main_window)
{
	_main_window = main_window;

    setMinimumWidth(200);
}

//==============================================================================
//==============================================================================

void EdSpriteProperties::buildProperties (void)
{
    clearProperties();

    KeyedSpriteResource* sprite = _main_window->getSprite ();
    if (!sprite)
        return;

    sprite->archiveWrite(&_properties);

    // Get the properties
    std::vector<ArchiveData*>& properties = _properties.getProperties();

    for (int i = 0; i < properties.size(); ++i) {
        ArchiveData *data = properties[i];
        const DTcharacter *type = data->dataKind();
    
        QListWidgetItem *list_item = new QListWidgetItem();
        addItem(list_item);
        
        if ( data->isBitfield() ) {
            EdSpritePropertyBitfieldField *itemWidget = new EdSpritePropertyBitfieldField(this, _main_window, data);
            setItemWidget(list_item,itemWidget);
            list_item->setSizeHint(itemWidget->minimumSize());

            connect (   this,       SIGNAL(doReadAllProperties()),
                        itemWidget, SLOT(doReadParams()));

        } else if ( String(type) == String("bool")) {
            EdSpritePropertyBoolField *itemWidget = new EdSpritePropertyBoolField(this, _main_window, data);
            setItemWidget(list_item,itemWidget);
            list_item->setSizeHint(itemWidget->minimumSize());

            connect (   this,       SIGNAL(doReadAllProperties()),
                        itemWidget, SLOT(doReadParams()));
            
        } else {
            EdSpritePropertyDefaultField *itemWidget = new EdSpritePropertyDefaultField(this, _main_window, data);
            setItemWidget(list_item,itemWidget);
            list_item->setSizeHint(itemWidget->minimumSize());

            connect (   this,       SIGNAL(doReadAllProperties()),
                        itemWidget, SLOT(doReadParams()));
            
        }
        
    }

}

//==============================================================================
//==============================================================================

void EdSpriteProperties::clearProperties (void)
{
    // Disconnect any slots from previous properties
    disconnect(this, SIGNAL(doReadAllProperties()), 0, 0);

    // Disconnect all children
    QList<QWidget*> widgetList = findChildren<QWidget *>("prop");
    for (auto i = widgetList.begin(); i != widgetList.end(); ++i) {
        (**i).blockSignals(true);
    }

    clear();
    _properties.clear();
}

//==============================================================================
//==============================================================================

void EdSpriteProperties::onSpriteChanged (void)
{
    emit doReadAllProperties();
}

void EdSpriteProperties::onSelectionChanged (void)
{
    buildProperties();
}

//==============================================================================
//==============================================================================


#include "moc_EdSpriteProperties.cpp"

