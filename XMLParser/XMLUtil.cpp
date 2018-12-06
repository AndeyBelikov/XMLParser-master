#include "stdafx.h"
#include <string>
#include "XMLUtil.h"


using std::string;

XMLUtil::XMLUtil()
{
}


XMLUtil::~XMLUtil()
{
}

string XMLUtil::formElement(const string &elementName, 
							const string &elementValue, 
							const string &attribuitesStringlEmentValue, 
							const string &subElementString)
{
	string sElement;
	// if element name is empty, return null string.
	if (!elementName.empty())
	{
		sElement = "<" + elementName;

		if (!attribuitesStringlEmentValue.empty())
		{
			sElement += " " + attribuitesStringlEmentValue;
		}
	
		if ((elementValue.empty()) && (subElementString.empty()))
		{
			// using short-cut notation when element value 
			// is empty and there are no subelements.
			sElement += "/>\n";
		}
		else
		{
			sElement += ">";

			if (!elementValue.empty())
			{
				string sTmpStr = elementValue;
				sElement += sTmpStr;
			}
			if (!subElementString.empty())
			{
				sElement += "\n" + subElementString;
			}
				
			sElement += "</" + elementName + ">\n";
		}
	}
	return sElement;
}


string XMLUtil::formAttribute(const string &attributeName, const string &attributeValue)
{
	string sAttribute;
	// return empty string, if attribute name is null.
	if (!attributeName.empty())
	{
		sAttribute = attributeName;
		sAttribute += "=\"";
		string sAttributeValue(attributeValue);
		sAttribute += sAttributeValue;
		sAttribute += "\" ";
	}
	return sAttribute;
}