/****************************************************************************
**
** Copyright (C) 2006-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtXMLPatterns module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_ComparingAggregator_H
#define Patternist_ComparingAggregator_H

/**
 * @file qcomparingaggregator_p.h
 * @short Contains the implementations for the functions <tt>fn:max()</tt>, MaxFN,
 * and <tt>fn:min()</tt>, MinFN, and the class ComparingAggregator.
 */

#include "qabstractfloat_p.h"
#include "qdecimal_p.h"
#include "qcastingplatform_p.h"
#include "qcomparisonplatform_p.h"
#include "qliteral_p.h"
#include "qaggregator_p.h"
#include "quntypedatomicconverter_p.h"
#include "qpatternistlocale_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Base class for the implementations of the <tt>fn:min()</tt> and <tt>fn:max()</tt> function.
     *
     * What function that more specifically is
     * followed, depends on how the constructor is called.
     *
     * @see MaxFN
     * @see MinFN
     * @ingroup Patternist_functions
     * @author Frans Englich <fenglich@trolltech.com>
     */
    template <AtomicComparator::Operator oper, AtomicComparator::ComparisonResult result>
    class ComparingAggregator : public Aggregator,
                                public ComparisonPlatform<ComparingAggregator<oper, result>,
                                                          true, AtomicComparator::AsValueComparison,
                                                          ReportContext::FORG0006>,
                                public CastingPlatform<ComparingAggregator<oper, result>, true>
    {
    public:
        virtual Item evaluateSingleton(const DynamicContext::Ptr &context) const;
        virtual Expression::Ptr typeCheck(const StaticContext::Ptr &context,
                                          const SequenceType::Ptr &reqType);

        inline AtomicComparator::Operator operatorID() const
        {
            return oper;
        }

        inline ItemType::Ptr targetType() const
        {
            return BuiltinTypes::xsDouble;
        }

    private:
        inline Item applyNumericPromotion(const Item &old,
                                               const Item &nev,
                                               const Item &newVal) const;

        using ComparisonPlatform<ComparingAggregator<oper, result>,
                                 true,
                                 AtomicComparator::AsValueComparison,
                                 ReportContext::FORG0006>::comparator;
        using ComparisonPlatform<ComparingAggregator<oper, result>,
                                 true,
                                 AtomicComparator::AsValueComparison,
                                 ReportContext::FORG0006>::fetchComparator;
        using CastingPlatform<ComparingAggregator<oper, result>, true>::cast;
    };

#include "qcomparingaggregator.cpp"

    /**
     * @short An instantiation of ComparingAggregator suitable for <tt>fn:max()</tt>.
     *
     * @ingroup Patternist_functions
     */
    typedef ComparingAggregator<AtomicComparator::OperatorGreaterThan, AtomicComparator::GreaterThan> MaxFN;

    /**
     * @short An instantiation of ComparingAggregator suitable for <tt>fn:max()</tt>.
     *
     * @ingroup Patternist_functions
     */
    typedef ComparingAggregator<AtomicComparator::OperatorLessThan, AtomicComparator::LessThan> MinFN;
}

QT_END_NAMESPACE

QT_END_HEADER

#endif