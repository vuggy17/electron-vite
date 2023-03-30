  
GlobalizationJapanesePhoneticAnalyzerContract = (function () {
  var cls = function GlobalizationJapanesePhoneticAnalyzerContract() {
    };
  return cls;
}) ();
exports.GlobalizationJapanesePhoneticAnalyzerContract = GlobalizationJapanesePhoneticAnalyzerContract;


_DayOfWeek = function () {
  this.sunday = 0;
  this.monday = 1;
  this.tuesday = 2;
  this.wednesday = 3;
  this.thursday = 4;
  this.friday = 5;
  this.saturday = 6;
}
exports.DayOfWeek = new _DayOfWeek();

_LanguageLayoutDirection = function () {
  this.ltr = 0;
  this.rtl = 1;
  this.ttbLtr = 2;
  this.ttbRtl = 3;
}
exports.LanguageLayoutDirection = new _LanguageLayoutDirection();

ApplicationLanguages = (function () {
  var cls = function ApplicationLanguages() {
  };
  

  cls.getLanguagesForUser = function getLanguagesForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.primaryLanguageOverride = new String();
  cls.languages = new Object();
  cls.manifestLanguages = new Object();
  return cls;
}) ();
exports.ApplicationLanguages = ApplicationLanguages;

Calendar = (function () {
  var cls = function Calendar() {
    this.year = new Number();
    this.second = new Number();
    this.period = new Number();
    this.nanosecond = new Number();
    this.month = new Number();
    this.minute = new Number();
    this.numeralSystem = new String();
    this.era = new Number();
    this.hour = new Number();
    this.day = new Number();
    this.firstSecondInThisMinute = new Number();
    this.firstYearInThisEra = new Number();
    this.isDaylightSavingTime = new Boolean();
    this.languages = new Object();
    this.lastDayInThisMonth = new Number();
    this.lastEra = new Number();
    this.lastHourInThisPeriod = new Number();
    this.lastMinuteInThisHour = new Number();
    this.lastMonthInThisYear = new Number();
    this.lastSecondInThisMinute = new Number();
    this.lastYearInThisEra = new Number();
    this.dayOfWeek = new DayOfWeek();
    this.firstDayInThisMonth = new Number();
    this.lastPeriodInThisDay = new Number();
    this.firstEra = new Number();
    this.numberOfDaysInThisMonth = new Number();
    this.numberOfEras = new Number();
    this.numberOfHoursInThisPeriod = new Number();
    this.numberOfMinutesInThisHour = new Number();
    this.firstHourInThisPeriod = new Number();
    this.numberOfMonthsInThisYear = new Number();
    this.numberOfPeriodsInThisDay = new Number();
    this.numberOfSecondsInThisMinute = new Number();
    this.numberOfYearsInThisEra = new Number();
    this.firstMinuteInThisHour = new Number();
    this.resolvedLanguage = new String();
    this.firstMonthInThisYear = new Number();
    this.firstPeriodInThisDay = new Number();
  };
  
var cls = function Calendar(languages, calendar, clock, timeZoneId) {
      this.year = new Number();
      this.second = new Number();
      this.period = new Number();
      this.nanosecond = new Number();
      this.month = new Number();
      this.minute = new Number();
      this.numeralSystem = new String();
      this.era = new Number();
      this.hour = new Number();
      this.day = new Number();
      this.firstSecondInThisMinute = new Number();
      this.firstYearInThisEra = new Number();
      this.isDaylightSavingTime = new Boolean();
      this.languages = new Object();
      this.lastDayInThisMonth = new Number();
      this.lastEra = new Number();
      this.lastHourInThisPeriod = new Number();
      this.lastMinuteInThisHour = new Number();
      this.lastMonthInThisYear = new Number();
      this.lastSecondInThisMinute = new Number();
      this.lastYearInThisEra = new Number();
      this.dayOfWeek = new DayOfWeek();
      this.firstDayInThisMonth = new Number();
      this.lastPeriodInThisDay = new Number();
      this.firstEra = new Number();
      this.numberOfDaysInThisMonth = new Number();
      this.numberOfEras = new Number();
      this.numberOfHoursInThisPeriod = new Number();
      this.numberOfMinutesInThisHour = new Number();
      this.firstHourInThisPeriod = new Number();
      this.numberOfMonthsInThisYear = new Number();
      this.numberOfPeriodsInThisDay = new Number();
      this.numberOfSecondsInThisMinute = new Number();
      this.numberOfYearsInThisEra = new Number();
      this.firstMinuteInThisHour = new Number();
      this.resolvedLanguage = new String();
      this.firstMonthInThisYear = new Number();
      this.firstPeriodInThisDay = new Number();
};

var cls = function Calendar(languages) {
      this.year = new Number();
      this.second = new Number();
      this.period = new Number();
      this.nanosecond = new Number();
      this.month = new Number();
      this.minute = new Number();
      this.numeralSystem = new String();
      this.era = new Number();
      this.hour = new Number();
      this.day = new Number();
      this.firstSecondInThisMinute = new Number();
      this.firstYearInThisEra = new Number();
      this.isDaylightSavingTime = new Boolean();
      this.languages = new Object();
      this.lastDayInThisMonth = new Number();
      this.lastEra = new Number();
      this.lastHourInThisPeriod = new Number();
      this.lastMinuteInThisHour = new Number();
      this.lastMonthInThisYear = new Number();
      this.lastSecondInThisMinute = new Number();
      this.lastYearInThisEra = new Number();
      this.dayOfWeek = new DayOfWeek();
      this.firstDayInThisMonth = new Number();
      this.lastPeriodInThisDay = new Number();
      this.firstEra = new Number();
      this.numberOfDaysInThisMonth = new Number();
      this.numberOfEras = new Number();
      this.numberOfHoursInThisPeriod = new Number();
      this.numberOfMinutesInThisHour = new Number();
      this.firstHourInThisPeriod = new Number();
      this.numberOfMonthsInThisYear = new Number();
      this.numberOfPeriodsInThisDay = new Number();
      this.numberOfSecondsInThisMinute = new Number();
      this.numberOfYearsInThisEra = new Number();
      this.firstMinuteInThisHour = new Number();
      this.resolvedLanguage = new String();
      this.firstMonthInThisYear = new Number();
      this.firstPeriodInThisDay = new Number();
};

var cls = function Calendar(languages, calendar, clock) {
      this.year = new Number();
      this.second = new Number();
      this.period = new Number();
      this.nanosecond = new Number();
      this.month = new Number();
      this.minute = new Number();
      this.numeralSystem = new String();
      this.era = new Number();
      this.hour = new Number();
      this.day = new Number();
      this.firstSecondInThisMinute = new Number();
      this.firstYearInThisEra = new Number();
      this.isDaylightSavingTime = new Boolean();
      this.languages = new Object();
      this.lastDayInThisMonth = new Number();
      this.lastEra = new Number();
      this.lastHourInThisPeriod = new Number();
      this.lastMinuteInThisHour = new Number();
      this.lastMonthInThisYear = new Number();
      this.lastSecondInThisMinute = new Number();
      this.lastYearInThisEra = new Number();
      this.dayOfWeek = new DayOfWeek();
      this.firstDayInThisMonth = new Number();
      this.lastPeriodInThisDay = new Number();
      this.firstEra = new Number();
      this.numberOfDaysInThisMonth = new Number();
      this.numberOfEras = new Number();
      this.numberOfHoursInThisPeriod = new Number();
      this.numberOfMinutesInThisHour = new Number();
      this.firstHourInThisPeriod = new Number();
      this.numberOfMonthsInThisYear = new Number();
      this.numberOfPeriodsInThisDay = new Number();
      this.numberOfSecondsInThisMinute = new Number();
      this.numberOfYearsInThisEra = new Number();
      this.firstMinuteInThisHour = new Number();
      this.resolvedLanguage = new String();
      this.firstMonthInThisYear = new Number();
      this.firstPeriodInThisDay = new Number();
};


  cls.prototype.changeTimeZone = function changeTimeZone(timeZoneId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="timeZoneId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.timeZoneAsString = function timeZoneAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.timeZoneAsString = function timeZoneAsString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addDays = function addDays(days) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="days" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.dayAsString = function dayAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.dayAsPaddedString = function dayAsPaddedString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.dayOfWeekAsString = function dayOfWeekAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.dayOfWeekAsString = function dayOfWeekAsString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.dayOfWeekAsSoloString = function dayOfWeekAsSoloString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.dayOfWeekAsSoloString = function dayOfWeekAsSoloString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addPeriods = function addPeriods(periods) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="periods" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.periodAsString = function periodAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.periodAsString = function periodAsString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addHours = function addHours(hours) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="hours" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.hourAsString = function hourAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.hourAsPaddedString = function hourAsPaddedString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addMinutes = function addMinutes(minutes) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minutes" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.minuteAsString = function minuteAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.minuteAsPaddedString = function minuteAsPaddedString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addSeconds = function addSeconds(seconds) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="seconds" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.secondAsString = function secondAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.secondAsPaddedString = function secondAsPaddedString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addNanoseconds = function addNanoseconds(nanoseconds) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="nanoseconds" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.nanosecondAsString = function nanosecondAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.nanosecondAsPaddedString = function nanosecondAsPaddedString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.compare = function compare(other) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="other" type="Calendar">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.compareDateTime = function compareDateTime(other) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="other" type="Date">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.copyTo = function copyTo(other) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="other" type="Calendar">A param.</param>
    /// </signature>
  }


  cls.prototype.getTimeZone = function getTimeZone() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.clone = function clone() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Calendar" />
    /// </signature>
    return new Calendar();
  }


  cls.prototype.setToMin = function setToMin() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.setToMax = function setToMax() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getCalendarSystem = function getCalendarSystem() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.changeCalendarSystem = function changeCalendarSystem(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getClock = function getClock() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.changeClock = function changeClock(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getDateTime = function getDateTime() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Date" />
    /// </signature>
    return new Date();
  }


  cls.prototype.setDateTime = function setDateTime(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Date">A param.</param>
    /// </signature>
  }


  cls.prototype.setToNow = function setToNow() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.addEras = function addEras(eras) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="eras" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.eraAsString = function eraAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.eraAsString = function eraAsString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addYears = function addYears(years) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="years" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.yearAsString = function yearAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.yearAsTruncatedString = function yearAsTruncatedString(remainingDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="remainingDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.yearAsPaddedString = function yearAsPaddedString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addMonths = function addMonths(months) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="months" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.monthAsString = function monthAsString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.monthAsString = function monthAsString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.monthAsSoloString = function monthAsSoloString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.prototype.monthAsSoloString = function monthAsSoloString(idealLength) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="idealLength" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.monthAsNumericString = function monthAsNumericString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.monthAsPaddedNumericString = function monthAsPaddedNumericString(minDigits) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minDigits" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.addWeeks = function addWeeks(weeks) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="weeks" type="Number">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.Calendar = Calendar;

CalendarIdentifiers = (function () {
  var cls = function CalendarIdentifiers() {
  };
  

  cls.julian = new String();
  cls.gregorian = new String();
  cls.hebrew = new String();
  cls.hijri = new String();
  cls.japanese = new String();
  cls.korean = new String();
  cls.taiwan = new String();
  cls.thai = new String();
  cls.umAlQura = new String();
  cls.persian = new String();
  cls.chineseLunar = new String();
  cls.vietnameseLunar = new String();
  cls.taiwanLunar = new String();
  cls.koreanLunar = new String();
  cls.japaneseLunar = new String();
  return cls;
}) ();
exports.CalendarIdentifiers = CalendarIdentifiers;

ClockIdentifiers = (function () {
  var cls = function ClockIdentifiers() {
  };
  

  cls.twelveHour = new String();
  cls.twentyFourHour = new String();
  return cls;
}) ();
exports.ClockIdentifiers = ClockIdentifiers;

CurrencyAmount = (function () {
  var cls = function CurrencyAmount() {
    this.amount = new String();
    this.currency = new String();
  };
  
var cls = function CurrencyAmount(amount, currency) {
      this.amount = new String();
      this.currency = new String();
};


  return cls;
}) ();
exports.CurrencyAmount = CurrencyAmount;

CurrencyIdentifiers = (function () {
  var cls = function CurrencyIdentifiers() {
  };
  

  cls.hNL = new String();
  cls.aED = new String();
  cls.aFN = new String();
  cls.aLL = new String();
  cls.aMD = new String();
  cls.aNG = new String();
  cls.aOA = new String();
  cls.aRS = new String();
  cls.aUD = new String();
  cls.aWG = new String();
  cls.aZN = new String();
  cls.bAM = new String();
  cls.bBD = new String();
  cls.bDT = new String();
  cls.bGN = new String();
  cls.bHD = new String();
  cls.bIF = new String();
  cls.bMD = new String();
  cls.bND = new String();
  cls.bOB = new String();
  cls.bRL = new String();
  cls.bSD = new String();
  cls.bTN = new String();
  cls.bWP = new String();
  cls.bYR = new String();
  cls.bZD = new String();
  cls.cAD = new String();
  cls.cDF = new String();
  cls.cHF = new String();
  cls.cLP = new String();
  cls.cNY = new String();
  cls.cOP = new String();
  cls.cRC = new String();
  cls.cUP = new String();
  cls.cVE = new String();
  cls.cZK = new String();
  cls.dJF = new String();
  cls.dKK = new String();
  cls.dOP = new String();
  cls.dZD = new String();
  cls.eGP = new String();
  cls.eRN = new String();
  cls.eTB = new String();
  cls.eUR = new String();
  cls.fJD = new String();
  cls.fKP = new String();
  cls.gBP = new String();
  cls.gEL = new String();
  cls.gHS = new String();
  cls.gIP = new String();
  cls.gMD = new String();
  cls.gNF = new String();
  cls.gTQ = new String();
  cls.gYD = new String();
  cls.hKD = new String();
  cls.rON = new String();
  cls.hRK = new String();
  cls.hTG = new String();
  cls.hUF = new String();
  cls.iDR = new String();
  cls.iLS = new String();
  cls.iNR = new String();
  cls.iQD = new String();
  cls.iRR = new String();
  cls.iSK = new String();
  cls.jMD = new String();
  cls.jOD = new String();
  cls.jPY = new String();
  cls.kES = new String();
  cls.kGS = new String();
  cls.kHR = new String();
  cls.kMF = new String();
  cls.kPW = new String();
  cls.kRW = new String();
  cls.kWD = new String();
  cls.kYD = new String();
  cls.kZT = new String();
  cls.lAK = new String();
  cls.lBP = new String();
  cls.lKR = new String();
  cls.lRD = new String();
  cls.lSL = new String();
  cls.lTL = new String();
  cls.lVL = new String();
  cls.lYD = new String();
  cls.mAD = new String();
  cls.mDL = new String();
  cls.mGA = new String();
  cls.mKD = new String();
  cls.mMK = new String();
  cls.mNT = new String();
  cls.mOP = new String();
  cls.mRO = new String();
  cls.mUR = new String();
  cls.mVR = new String();
  cls.mWK = new String();
  cls.mXN = new String();
  cls.mYR = new String();
  cls.mZN = new String();
  cls.nAD = new String();
  cls.nGN = new String();
  cls.nIO = new String();
  cls.nOK = new String();
  cls.nPR = new String();
  cls.nZD = new String();
  cls.oMR = new String();
  cls.pAB = new String();
  cls.pEN = new String();
  cls.pGK = new String();
  cls.pHP = new String();
  cls.pKR = new String();
  cls.pLN = new String();
  cls.pYG = new String();
  cls.qAR = new String();
  cls.rSD = new String();
  cls.rUB = new String();
  cls.rWF = new String();
  cls.sAR = new String();
  cls.sBD = new String();
  cls.sCR = new String();
  cls.sDG = new String();
  cls.sEK = new String();
  cls.sGD = new String();
  cls.sHP = new String();
  cls.sLL = new String();
  cls.sOS = new String();
  cls.sRD = new String();
  cls.sTD = new String();
  cls.sYP = new String();
  cls.sZL = new String();
  cls.tHB = new String();
  cls.tJS = new String();
  cls.tMT = new String();
  cls.tND = new String();
  cls.tOP = new String();
  cls.tRY = new String();
  cls.tTD = new String();
  cls.tWD = new String();
  cls.tZS = new String();
  cls.uAH = new String();
  cls.uGX = new String();
  cls.uSD = new String();
  cls.uYU = new String();
  cls.uZS = new String();
  cls.vEF = new String();
  cls.vND = new String();
  cls.vUV = new String();
  cls.wST = new String();
  cls.xAF = new String();
  cls.xCD = new String();
  cls.xOF = new String();
  cls.xPF = new String();
  cls.xXX = new String();
  cls.yER = new String();
  cls.zAR = new String();
  cls.zMW = new String();
  cls.zWL = new String();
  cls.bYN = new String();
  cls.sSP = new String();
  cls.sTN = new String();
  cls.vES = new String();
  cls.mRU = new String();
  return cls;
}) ();
exports.CurrencyIdentifiers = CurrencyIdentifiers;

GeographicRegion = (function () {
  var cls = function GeographicRegion() {
    this.code = new String();
    this.codeThreeDigit = new String();
    this.codeThreeLetter = new String();
    this.codeTwoLetter = new String();
    this.currenciesInUse = new Object();
    this.displayName = new String();
    this.nativeName = new String();
  };
  
var cls = function GeographicRegion(geographicRegionCode) {
      this.code = new String();
      this.codeThreeDigit = new String();
      this.codeThreeLetter = new String();
      this.codeTwoLetter = new String();
      this.currenciesInUse = new Object();
      this.displayName = new String();
      this.nativeName = new String();
};


  cls.isSupported = function isSupported(geographicRegionCode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="geographicRegionCode" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  return cls;
}) ();
exports.GeographicRegion = GeographicRegion;

JapanesePhoneme = (function () {
  var cls = function JapanesePhoneme() {
    this.displayText = new String();
    this.isPhraseStart = new Boolean();
    this.yomiText = new String();
  };
  

  return cls;
}) ();
exports.JapanesePhoneme = JapanesePhoneme;

JapanesePhoneticAnalyzer = (function () {
  var cls = function JapanesePhoneticAnalyzer() {
  };
  

  cls.getWords = function getWords(input) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="input" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }

cls.getWords = function getWords(input, monoRuby) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="input" type="String">A param.</param>
    /// <param name="monoRuby" type="Boolean">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.JapanesePhoneticAnalyzer = JapanesePhoneticAnalyzer;

Language = (function () {
  var cls = function Language() {
    this.displayName = new String();
    this.languageTag = new String();
    this.nativeName = new String();
    this.script = new String();
    this.layoutDirection = new LanguageLayoutDirection();
    this.abbreviatedName = new String();
  };
  
var cls = function Language(languageTag) {
      this.displayName = new String();
      this.languageTag = new String();
      this.nativeName = new String();
      this.script = new String();
      this.layoutDirection = new LanguageLayoutDirection();
      this.abbreviatedName = new String();
};


  cls.prototype.getExtensionSubtags = function getExtensionSubtags(singleton) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="singleton" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.getMuiCompatibleLanguageListFromLanguageTags = function getMuiCompatibleLanguageListFromLanguageTags(languageTags) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="languageTags" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.trySetInputMethodLanguageTag = function trySetInputMethodLanguageTag(languageTag) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="languageTag" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.isWellFormed = function isWellFormed(languageTag) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="languageTag" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.currentInputMethodLanguageTag = new String();
  return cls;
}) ();
exports.Language = Language;

NumeralSystemIdentifiers = (function () {
  var cls = function NumeralSystemIdentifiers() {
  };
  

  cls.fullWide = new String();
  cls.arab = new String();
  cls.arabExt = new String();
  cls.bali = new String();
  cls.beng = new String();
  cls.cham = new String();
  cls.deva = new String();
  cls.mymrShan = new String();
  cls.gujr = new String();
  cls.guru = new String();
  cls.haniDec = new String();
  cls.java = new String();
  cls.kali = new String();
  cls.khmr = new String();
  cls.knda = new String();
  cls.lana = new String();
  cls.lanaTham = new String();
  cls.laoo = new String();
  cls.latn = new String();
  cls.lepc = new String();
  cls.limb = new String();
  cls.mlym = new String();
  cls.mong = new String();
  cls.mtei = new String();
  cls.mymr = new String();
  cls.nkoo = new String();
  cls.olck = new String();
  cls.orya = new String();
  cls.saur = new String();
  cls.sund = new String();
  cls.talu = new String();
  cls.tamlDec = new String();
  cls.telu = new String();
  cls.thai = new String();
  cls.tibt = new String();
  cls.vaii = new String();
  cls.mathBold = new String();
  cls.mathDbl = new String();
  cls.mathMono = new String();
  cls.mathSanb = new String();
  cls.mathSans = new String();
  cls.osma = new String();
  cls.zmthBold = new String();
  cls.zmthDbl = new String();
  cls.zmthMono = new String();
  cls.zmthSanb = new String();
  cls.zmthSans = new String();
  cls.brah = new String();
  return cls;
}) ();
exports.NumeralSystemIdentifiers = NumeralSystemIdentifiers;

