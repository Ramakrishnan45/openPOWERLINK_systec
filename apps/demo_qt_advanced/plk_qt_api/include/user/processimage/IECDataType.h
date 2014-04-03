/**
********************************************************************************
\file   IECDataType.h

\brief  The Datatypes derived from the IEC standards.

\author Ramakrishnan Periyakaruppan

\copyright (c) 2014, Kalycito Infotech Private Limited
					 All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the copyright holders nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef _IECDATATYPE_H_
#define _IECDATATYPE_H_
/*******************************************************************************
* INCLUDES
*******************************************************************************/
#include <string>

/**
 * \brief IECDataType of the Channels.
 * refer Enum - IECDataType
 */
namespace IECDataType
{
	/**
	 * List of datatypes derived from the IEC standards.
	 */
	enum IECDataType
	{
		UNDEFINED = 0,  ///< Undefined (Used in error handling)
		Bool,           ///< Bool,BitString (1 bit)
		Byte,           ///< Byte (8 bit)
		Char,           ///< Char (8 bit)
		Word,           ///< Word (16 bit)
		DWord,          ///< Dword (32 bit)
		LWord,          ///< Lword (64 bit)
		SInt,           ///< Signed short integer (1 byte)
		Int,            ///< Signed integer (2 byte)
		DInt,           ///< Double integer (4 byte)
		LInt,           ///< Long integer (8 byte)
		USInt,          ///< Unsigned short integer (1 byte)
		UInt,           ///< Unsigned integer (2 byte)
		UDInt,          ///< Unsigned double integer (4 byte)
		ULInt,          ///< Unsigned long integer (8 byte)
		Real,           ///< REAL (4 byte)
		LReal,          ///< LREAL (8 byte)
		String,         ///< Variable length single byte character string
		WString         ///< Variable length double byte character string
	};

} // namespace IECDataType

/**
 * \brief   Convert string value to the equivalent IECDataType.
 * \param[in]  iecDataTypeStr  The string with IEC datatype.
 * \return The matching IECDataType.
 */
IECDataType::IECDataType GetIECDatatype(const std::string& iecDataTypeStr);

#endif // _IECDATATYPE_H_
