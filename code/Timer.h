
#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	Timer();

	/**
	 * Empty Destructor
	 */
	virtual ~Timer();



	/**
	 * Timer initalizing routine
	 */
	void initTimer()
	{
	}


	/**
	 * Set a function to the interrupttable. the function and the timer number is
	 * needed.
	 * @param  pfFnction
	 * @param  timerNo
	 */
	void setInterrupt(int pfFnction, void timerNo)
	{
	}

private:
	// Private attributes
	//  

	// Time period in microseconds
	int periode;

	// Private attribute accessor methods
	//  


	/**
	 * Set the value of periode
	 * Time period in microseconds
	 * @param value the new value of periode
	 */
	void setPeriode(int value)
	{
		periode = value;
	}

	/**
	 * Get the value of periode
	 * Time period in microseconds
	 * @return the value of periode
	 */
	int getPeriode()
	{
		return periode;
	}

	void initAttributes();

};

#endif // TIMER_H
