/*
 *
 *  Copyright (C) 2010, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module: dcmsr
 *
 *  Author: Joerg Riesmeier
 *
 *  Purpose:
 *    classes: DSRGraphicData3DItem, DSRGraphicData3DList
 *
 *  Last Update:      $Author: joergr $
 *  Update Date:      $Date: 2010-09-28 14:08:14 $
 *  CVS/RCS Revision: $Revision: 1.1 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#ifndef DSRSC3GR_H
#define DSRSC3GR_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrtlist.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for graphic data (3D) items
 */
class DSRGraphicData3DItem
{
  public:

    /** (default) constructor
     ** @param  x  optional x value
     *  @param  y  optional y value
     *  @param  z  optional z value
     */
    DSRGraphicData3DItem(const Float32 x = 0,
                         const Float32 y = 0,
                         const Float32 z = 0)
      : XCoord(x),
        YCoord(y),
        ZCoord(z)
    {
    }

    /** comparison operator
     ** @param  item  item with which the (x,y,z) triplet should be compared
     ** @return OFTrue if both triplets are equal, OFFalse otherwise
     */
    inline OFBool operator==(const DSRGraphicData3DItem &item) const
    {
        return (item.XCoord == XCoord) && (item.YCoord == YCoord) && (item.ZCoord == ZCoord);
    }

    /** comparison operator
     ** @param  item  item with which the (x,y,z) triplet should be compared
     ** @return true if not equal, false if equal
     */
    inline OFBool operator!=(const DSRGraphicData3DItem &item) const
    {
        return (item.XCoord != XCoord) || (item.YCoord != YCoord) || (item.ZCoord != ZCoord);
    }

    /* copy constructor and assignment operator are defined implicitly */

    /// x value (VR=FL)
    Float32 XCoord;
    /// y value (VR=FL)
    Float32 YCoord;
    /// z value (VR=FL)
    Float32 ZCoord;
};


/** Class for graphic data (3D) lists
 */
class DSRGraphicData3DList
  : public DSRListOfItems<DSRGraphicData3DItem>
{

  public:

    /** default constructor
     */
    DSRGraphicData3DList();

    /** copy constructor
     ** @param  lst  list to be copied
     */
    DSRGraphicData3DList(const DSRGraphicData3DList &lst);

    /** destructor
     */
    virtual ~DSRGraphicData3DList();

    /** assignment operator
     ** @param  lst  list to be copied
     ** @return reference to this list after 'lst' has been copied
     */
    DSRGraphicData3DList &operator=(const DSRGraphicData3DList &lst);

    /** print list of graphic data.
     *  The output of a typical list looks like this: 0/0/0,127/127/127,255/255/255
     ** @param  stream            output stream to which the list should be printed
     *  @param  flags             flag used to customize the output (see DSRTypes::PF_xxx)
     *  @param  tripletSeparator  character specifying the separator between the value triplets
     *  @param  itemSeparator     character specifying the separator between the list items
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition print(STD_NAMESPACE ostream &stream,
                      const size_t flags = 0,
                      const char tripletSeparator = '/',
                      const char itemSeparator = ',') const;

    /** read list of graphic data
     ** @param  dataset  DICOM dataset from which the list should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition read(DcmItem &dataset);

    /** write list of graphic data
     ** @param  dataset  DICOM dataset to which the list should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition write(DcmItem &dataset) const;

    /** get reference to the specified item
     ** @param  idx  index of the item to be returned (starting from 1)
     ** @return reference to the specified item if successful, EmptyItem otherwise
     */
    const DSRGraphicData3DItem &getItem(const size_t idx) const;

    /** get copy of the specified value triplet
     ** @param  idx  index of the value triplet to be returned (starting from 1)
     *  @param  x    x value of the specified index (set to 0 first)
     *  @param  y    y value of the specified index (set to 0 first)
     *  @param  z    z value of the specified index (set to 0 first)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition getItem(const size_t idx,
                        Float32 &x,
                        Float32 &y,
                        Float32 &z) const;

    /** add value triplet to the list
     ** @param  x  x value to be added
     *  @param  y  y value to be added
     *  @param  z  z value to be added
     */
    void addItem(const Float32 x,
                 const Float32 y,
                 const Float32 z);

    /** put list of graphic data as a string.
     *  This function expects the same input format as created by print(), i.e. a comma
     *  separated list of numerical value triplets.
     ** @param  stringValue  string value to be set
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition putString(const char *stringValue);
};


#endif


/*
 *  CVS/RCS Log:
 *  $Log: dsrsc3gr.h,v $
 *  Revision 1.1  2010-09-28 14:08:14  joergr
 *  Added support for Colon CAD SR which requires a new value type (SCOORD3D).
 *
 *
 *
 */