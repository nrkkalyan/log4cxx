/*
 * Copyright 2003,2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <log4cxx/logstring.h>
#include "xlogger.h"
#include <log4cxx/level.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/spi/location/locationinfo.h>
#include <log4cxx/spi/loggerrepository.h>


using namespace log4cxx;
using namespace log4cxx::spi;

IMPLEMENT_LOG4CXX_OBJECT(XLogger)
IMPLEMENT_LOG4CXX_OBJECT(XFactory)

XFactoryPtr XLogger::factory = new XFactory();

void XLogger::lethal(const LogString& message, const LocationInfo& locationInfo)
{
        if (repository->isDisabled(XLevel::LETHAL_INT))
        {
                return;
        }

        if (XLevel::LETHAL->isGreaterOrEqual(this->getEffectiveLevel()))
        {
                forcedLog(XLevel::LETHAL, message, locationInfo);
        }
}

void XLogger::lethal(const LogString& message)
{
        if (repository->isDisabled(XLevel::LETHAL_INT))
        {
                return;
        }

        if (XLevel::LETHAL->isGreaterOrEqual(this->getEffectiveLevel()))
        {
                forcedLog(XLevel::LETHAL, message, LocationInfo::getLocationUnavailable());
        }
}

LoggerPtr XLogger::getLogger(const LogString& name)
{
        return LogManager::getLogger(name, factory);
}

LoggerPtr XLogger::getLogger(const helpers::Class& clazz)
{
        return XLogger::getLogger(clazz.getName());
}

void XLogger::trace(const LogString& message, const LocationInfo& locationInfo)
{
        if (repository->isDisabled(XLevel::TRACE_INT))
        {
                return;
        }

        if (XLevel::TRACE->isGreaterOrEqual(this->getEffectiveLevel()))
        {
                forcedLog(XLevel::TRACE, message, locationInfo);
        }
}

void XLogger::trace(const LogString& message)
{
        if (repository->isDisabled(XLevel::TRACE_INT))
        {
                return;
        }

        if (XLevel::TRACE->isGreaterOrEqual(this->getEffectiveLevel()))
        {
                forcedLog(XLevel::TRACE, message, LocationInfo::getLocationUnavailable());
        }
}

XFactory::XFactory()
{
}

LoggerPtr XFactory::makeNewLoggerInstance(log4cxx::helpers::Pool& pool, 
       const LogString& name) const
{
        return new XLogger(pool, name);
}
