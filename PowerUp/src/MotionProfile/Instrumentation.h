#ifndef _INSTRUMENTATION_HG_
#define _INSTRUMENTATION_HG_

#include <iostream>
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <iomanip>

class Instrumentation
{
public:
	static void OnNoProgress()
	{
		std::cout << "NOPROGRESS" << std::endl;
	}

	/**
	 *
	 */

	static void OnUnderrun()
	{
		std::cout << "UNDERRUN" << std::endl;
	}

	/**
	 *
	 */

	static const char* StrOutputEnable(unsigned int value)
	{
		static const char table[][6] = { " Dis ", " En ", "Hold ", "Inval" };
		if (value  > 3) value = 3;

		return table[value];
	}

	/**
	 *
	 */

	static void Process(MotionProfileStatus& status, double pos, double vel, double heading)
	{
		static double timeout = 0;
		static int count = 0;

		const char delim[] = "\t";
		const char endline[] = "\n";

		double now = GetTime();

		if ((now - timeout) <= 0.2) return;

		timeout = now;

		if (--count <= 0)
		{
			count = 8;
			std::cout
				<< "       outEn" << delim
				<< "topBufferCnt" << delim
				<< "topBufferRem" << delim
				<< "btmBufferCnt" << delim
				<< "     IsValid" << delim
				<< " HasUnderrun" << delim
				<< "  IsUnderrun" << delim
				<< "      IsLast" << delim
				<< "     targPos" << delim
				<< "     targVel" << delim
				<< "    SlotSel0" << delim
				<< "   timeDurMs" << delim << endline;
		}

		std::cout
			<< std::setw(12)<< StrOutputEnable(status.outputEnable) << delim
			<< std::setw(12)<< status.topBufferCnt << delim << delim
			<< std::setw(12)<< status.topBufferRem << delim << delim
			<< std::setw(12)<< status.btmBufferCnt << delim
			<< std::setw(12)<< (status.activePointValid ? "true" : "false") << delim
			<< std::setw(12)<< (status.hasUnderrun ? "true" : "false") << delim
			<< std::setw(12)<< (status.isUnderrun ? "true" : "false") << delim
			<< std::setw(12)<< (status.isLast ? "true" : "false") << delim
			<< std::setw(12)<< pos << delim
			<< std::setw(12)<< vel << delim
			<< std::setw(12)<< status.profileSlotSelect0 << delim
			<< std::setw(12)<< status.timeDurMs << delim << endline;
	}
};

#endif
