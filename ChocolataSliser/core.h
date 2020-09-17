#pragma once

#define __ChocolataSlicer_Release_Version_ 0
#define __ChocolataSlicer_Major_Version_ 1
#define __ChocolataSlicer_Minor_Version_ 43
#define __ChocolataSlicer_Version_ "0.1.43"


#define __ChocolataSlicer_Link_ "https://github.com/bit-creator/ChocolataSlicer.git"
#define __ChocolataSlicer_Documentation_Link_ "https://github.com/bit-creator/ChocolataSlicer.git"



#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>
#include <cinder/Log.h>


struct ProfileResult {
	std::string Name;
	std::chrono::duration<double, std::micro> Start;
	std::chrono::microseconds ElapsedTime;
	std::thread::id ThreadID;
};

struct InstrumentationSession {
	std::string Name;
};



class Instrumentor {
    private :
        Instrumentor() {
        }


    	std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;

    public : // Singleton
        static Instrumentor& Get() { static Instrumentor ins; return ins; }

    public : // Fields

        ci::log::LoggerFile     _slicerLogger = ci::log::LoggerFile("assets/config/ChocolataSlicer.log", false);

        ci::log::LoggerFile     _firmwareLogger = ci::log::LoggerFile("assets/config/ChocolataFirmware.log", false);


    public :

        void BeginSession(const std::string& name, const std::string& filepath = "results.json") {
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) {
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open()) {
				m_CurrentSession = new InstrumentationSession({name});
				WriteHeader();
			}
			else {
			}
		}


		void EndSession() {
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}


        void WriteProfile(const ProfileResult& result) {
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}



        void WriteHeader() {
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		void WriteFooter() {
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		void InternalEndSession() {
			if (m_CurrentSession) {
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

};





class InstrumentationTimer {
    public:
    	InstrumentationTimer(const char* name)
    		: m_Name(name), m_Stopped(false) {
    		m_StartTimepoint = std::chrono::steady_clock::now();
    	}

	    ~InstrumentationTimer() {
	    	if (!m_Stopped)
	    		Stop();
	    }

	    void Stop() {
	    	auto endTimepoint = std::chrono::steady_clock::now();
	    	auto highResStart = std::chrono::duration<double, std::micro>{ m_StartTimepoint.time_since_epoch() };
	    	auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

	    	Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

	    	m_Stopped = true;
	    }

    private:
    	const char* m_Name;
    	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    	bool m_Stopped;

};


#define CHOCOLATA_SLIER_PROFILING 1
#if CHOCOLATA_SLIER_PROFILING
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define CHOCOLATA_SLIER_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define CHOCOLATA_SLIER_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define CHOCOLATA_SLIER_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define CHOCOLATA_SLIER_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define CHOCOLATA_SLIER_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define CHOCOLATA_SLIER_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define CHOCOLATA_SLIER_FUNC_SIG __func__
	#else
		#define CHOCOLATA_SLIER_FUNC_SIG "CHOCOLATA_SLIER_FUNC_SIG unknown!"
	#endif

	#define CHOCOLATA_SLIER_PROFILE_BEGIN_SESSION(name, filepath) Instrumentor::Get().BeginSession(name, filepath)
	#define CHOCOLATA_SLIER_PROFILE_END_SESSION() Instrumentor::Get().EndSession()
    #define CHOCOLATA_SLIER_PROFILE_SCOPE_LINE2(name, line) InstrumentationTimer timer##line(name)
											   
	#define CHOCOLATA_SLIER_PROFILE_SCOPE_LINE(name, line) CHOCOLATA_SLIER_PROFILE_SCOPE_LINE2(name, line)
	#define CHOCOLATA_SLIER_PROFILE_SCOPE(name) CHOCOLATA_SLIER_PROFILE_SCOPE_LINE(name, __LINE__)
	#define CHOCOLATA_SLIER_PROFILE_FUNCTION() CHOCOLATA_SLIER_PROFILE_SCOPE(CHOCOLATA_SLIER_FUNC_SIG)
#else
	#define CHOCOLATA_SLIER_PROFILE_BEGIN_SESSION(name, filepath)
	#define CHOCOLATA_SLIER_PROFILE_END_SESSION()
	#define CHOCOLATA_SLIER_PROFILE_SCOPE(name)
	#define CHOCOLATA_SLIER_PROFILE_FUNCTION()
#endif
