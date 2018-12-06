#pragma once
class XMLUtil
{
public:
	XMLUtil();
	~XMLUtil();

	//XMLUtil(const XMLUtil&) = delete;
	//XMLUtil& operator= (const XMLUtil&) = delete;

	//	This method takes the following parameters to form an
	//	XML element :
	//
	//	1. Element Name
	//	2. Element Value
	//	3. Attributes List String  (default argument)
	//	4. Sub Element String.  (default argument)
	//	This method returns the XML element string in the form a
	//	std::string.
	//
	//	If
	//	1. The element value is null, it returns the element
	//	string in a simple form (<ELEMENT NAME/>) as specified in XML spec.
	//	2. The elment name is null, it returns a null string.
	static std::string formElement(const std::string &elementName,
								   const std::string &elementValue = "",
							       const std::string &attribuitesStringlEmentValue = "",
							       const std::string &subElementString = "");

	//  This method takes the attribute name and value and forms
	//  an attribute string
	//  Attribute string can be passed to
	//  the method formElement() to attach the attribute to an
	//  element.
	//
	//  This method returns a null string if the attribute value
	//  is null.
	static std::string formAttribute(const std::string &attributeName,
								     const std::string &attributeValue);

};

