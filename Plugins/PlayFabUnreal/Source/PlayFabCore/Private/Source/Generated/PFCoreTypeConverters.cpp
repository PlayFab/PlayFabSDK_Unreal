// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#include "Generated/PFCoreTypeConverters.h"
#pragma push_macro("IN")
#undef IN


const FPFTitleActivationStatus ConvertTitleActivationStatusToUnreal(const PFTitleActivationStatus* enumVal)
{
	if (enumVal == nullptr) {
		return FPFTitleActivationStatus::None;
	}

	switch(*enumVal)
	{
	case PFTitleActivationStatus::None: return FPFTitleActivationStatus::None;
	case PFTitleActivationStatus::ActivatedTitleKey: return FPFTitleActivationStatus::ActivatedTitleKey;
	case PFTitleActivationStatus::PendingSteam: return FPFTitleActivationStatus::PendingSteam;
	case PFTitleActivationStatus::ActivatedSteam: return FPFTitleActivationStatus::ActivatedSteam;
	case PFTitleActivationStatus::RevokedSteam: return FPFTitleActivationStatus::RevokedSteam;
	default:
	return FPFTitleActivationStatus::None;
	}
}

const PFTitleActivationStatus ConvertTitleActivationStatusToPlayfab(TSharedPtr<const FPFTitleActivationStatus> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFTitleActivationStatus::None;
	}

	switch(*enumVal)
	{
	case FPFTitleActivationStatus::None: return PFTitleActivationStatus::None;
	case FPFTitleActivationStatus::ActivatedTitleKey: return PFTitleActivationStatus::ActivatedTitleKey;
	case FPFTitleActivationStatus::PendingSteam: return PFTitleActivationStatus::PendingSteam;
	case FPFTitleActivationStatus::ActivatedSteam: return PFTitleActivationStatus::ActivatedSteam;
	case FPFTitleActivationStatus::RevokedSteam: return PFTitleActivationStatus::RevokedSteam;
	default:
	return PFTitleActivationStatus::None;
	}
}

const FPFCurrency ConvertCurrencyToUnreal(const PFCurrency* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCurrency::AED;
	}

	switch(*enumVal)
	{
	case PFCurrency::AED: return FPFCurrency::AED;
	case PFCurrency::AFN: return FPFCurrency::AFN;
	case PFCurrency::ALL: return FPFCurrency::ALL;
	case PFCurrency::AMD: return FPFCurrency::AMD;
	case PFCurrency::ANG: return FPFCurrency::ANG;
	case PFCurrency::AOA: return FPFCurrency::AOA;
	case PFCurrency::ARS: return FPFCurrency::ARS;
	case PFCurrency::AUD: return FPFCurrency::AUD;
	case PFCurrency::AWG: return FPFCurrency::AWG;
	case PFCurrency::AZN: return FPFCurrency::AZN;
	case PFCurrency::BAM: return FPFCurrency::BAM;
	case PFCurrency::BBD: return FPFCurrency::BBD;
	case PFCurrency::BDT: return FPFCurrency::BDT;
	case PFCurrency::BGN: return FPFCurrency::BGN;
	case PFCurrency::BHD: return FPFCurrency::BHD;
	case PFCurrency::BIF: return FPFCurrency::BIF;
	case PFCurrency::BMD: return FPFCurrency::BMD;
	case PFCurrency::BND: return FPFCurrency::BND;
	case PFCurrency::BOB: return FPFCurrency::BOB;
	case PFCurrency::BRL: return FPFCurrency::BRL;
	case PFCurrency::BSD: return FPFCurrency::BSD;
	case PFCurrency::BTN: return FPFCurrency::BTN;
	case PFCurrency::BWP: return FPFCurrency::BWP;
	case PFCurrency::BYR: return FPFCurrency::BYR;
	case PFCurrency::BZD: return FPFCurrency::BZD;
	case PFCurrency::CAD: return FPFCurrency::CAD;
	case PFCurrency::CDF: return FPFCurrency::CDF;
	case PFCurrency::CHF: return FPFCurrency::CHF;
	case PFCurrency::CLP: return FPFCurrency::CLP;
	case PFCurrency::CNY: return FPFCurrency::CNY;
	case PFCurrency::COP: return FPFCurrency::COP;
	case PFCurrency::CRC: return FPFCurrency::CRC;
	case PFCurrency::CUC: return FPFCurrency::CUC;
	case PFCurrency::CUP: return FPFCurrency::CUP;
	case PFCurrency::CVE: return FPFCurrency::CVE;
	case PFCurrency::CZK: return FPFCurrency::CZK;
	case PFCurrency::DJF: return FPFCurrency::DJF;
	case PFCurrency::DKK: return FPFCurrency::DKK;
	case PFCurrency::DOP: return FPFCurrency::DOP;
	case PFCurrency::DZD: return FPFCurrency::DZD;
	case PFCurrency::EGP: return FPFCurrency::EGP;
	case PFCurrency::ERN: return FPFCurrency::ERN;
	case PFCurrency::ETB: return FPFCurrency::ETB;
	case PFCurrency::EUR: return FPFCurrency::EUR;
	case PFCurrency::FJD: return FPFCurrency::FJD;
	case PFCurrency::FKP: return FPFCurrency::FKP;
	case PFCurrency::GBP: return FPFCurrency::GBP;
	case PFCurrency::GEL: return FPFCurrency::GEL;
	case PFCurrency::GGP: return FPFCurrency::GGP;
	case PFCurrency::GHS: return FPFCurrency::GHS;
	case PFCurrency::GIP: return FPFCurrency::GIP;
	case PFCurrency::GMD: return FPFCurrency::GMD;
	case PFCurrency::GNF: return FPFCurrency::GNF;
	case PFCurrency::GTQ: return FPFCurrency::GTQ;
	case PFCurrency::GYD: return FPFCurrency::GYD;
	case PFCurrency::HKD: return FPFCurrency::HKD;
	case PFCurrency::HNL: return FPFCurrency::HNL;
	case PFCurrency::HRK: return FPFCurrency::HRK;
	case PFCurrency::HTG: return FPFCurrency::HTG;
	case PFCurrency::HUF: return FPFCurrency::HUF;
	case PFCurrency::IDR: return FPFCurrency::IDR;
	case PFCurrency::ILS: return FPFCurrency::ILS;
	case PFCurrency::IMP: return FPFCurrency::IMP;
	case PFCurrency::INR: return FPFCurrency::INR;
	case PFCurrency::IQD: return FPFCurrency::IQD;
	case PFCurrency::IRR: return FPFCurrency::IRR;
	case PFCurrency::ISK: return FPFCurrency::ISK;
	case PFCurrency::JEP: return FPFCurrency::JEP;
	case PFCurrency::JMD: return FPFCurrency::JMD;
	case PFCurrency::JOD: return FPFCurrency::JOD;
	case PFCurrency::JPY: return FPFCurrency::JPY;
	case PFCurrency::KES: return FPFCurrency::KES;
	case PFCurrency::KGS: return FPFCurrency::KGS;
	case PFCurrency::KHR: return FPFCurrency::KHR;
	case PFCurrency::KMF: return FPFCurrency::KMF;
	case PFCurrency::KPW: return FPFCurrency::KPW;
	case PFCurrency::KRW: return FPFCurrency::KRW;
	case PFCurrency::KWD: return FPFCurrency::KWD;
	case PFCurrency::KYD: return FPFCurrency::KYD;
	case PFCurrency::KZT: return FPFCurrency::KZT;
	case PFCurrency::LAK: return FPFCurrency::LAK;
	case PFCurrency::LBP: return FPFCurrency::LBP;
	case PFCurrency::LKR: return FPFCurrency::LKR;
	case PFCurrency::LRD: return FPFCurrency::LRD;
	case PFCurrency::LSL: return FPFCurrency::LSL;
	case PFCurrency::LYD: return FPFCurrency::LYD;
	case PFCurrency::MAD: return FPFCurrency::MAD;
	case PFCurrency::MDL: return FPFCurrency::MDL;
	case PFCurrency::MGA: return FPFCurrency::MGA;
	case PFCurrency::MKD: return FPFCurrency::MKD;
	case PFCurrency::MMK: return FPFCurrency::MMK;
	case PFCurrency::MNT: return FPFCurrency::MNT;
	case PFCurrency::MOP: return FPFCurrency::MOP;
	case PFCurrency::MRO: return FPFCurrency::MRO;
	case PFCurrency::MUR: return FPFCurrency::MUR;
	case PFCurrency::MVR: return FPFCurrency::MVR;
	case PFCurrency::MWK: return FPFCurrency::MWK;
	case PFCurrency::MXN: return FPFCurrency::MXN;
	case PFCurrency::MYR: return FPFCurrency::MYR;
	case PFCurrency::MZN: return FPFCurrency::MZN;
	case PFCurrency::NAD: return FPFCurrency::NAD;
	case PFCurrency::NGN: return FPFCurrency::NGN;
	case PFCurrency::NIO: return FPFCurrency::NIO;
	case PFCurrency::NOK: return FPFCurrency::NOK;
	case PFCurrency::NPR: return FPFCurrency::NPR;
	case PFCurrency::NZD: return FPFCurrency::NZD;
	case PFCurrency::OMR: return FPFCurrency::OMR;
	case PFCurrency::PAB: return FPFCurrency::PAB;
	case PFCurrency::PEN: return FPFCurrency::PEN;
	case PFCurrency::PGK: return FPFCurrency::PGK;
	case PFCurrency::PHP: return FPFCurrency::PHP;
	case PFCurrency::PKR: return FPFCurrency::PKR;
	case PFCurrency::PLN: return FPFCurrency::PLN;
	case PFCurrency::PYG: return FPFCurrency::PYG;
	case PFCurrency::QAR: return FPFCurrency::QAR;
	case PFCurrency::RON: return FPFCurrency::RON;
	case PFCurrency::RSD: return FPFCurrency::RSD;
	case PFCurrency::RUB: return FPFCurrency::RUB;
	case PFCurrency::RWF: return FPFCurrency::RWF;
	case PFCurrency::SAR: return FPFCurrency::SAR;
	case PFCurrency::SBD: return FPFCurrency::SBD;
	case PFCurrency::SCR: return FPFCurrency::SCR;
	case PFCurrency::SDG: return FPFCurrency::SDG;
	case PFCurrency::SEK: return FPFCurrency::SEK;
	case PFCurrency::SGD: return FPFCurrency::SGD;
	case PFCurrency::SHP: return FPFCurrency::SHP;
	case PFCurrency::SLL: return FPFCurrency::SLL;
	case PFCurrency::SOS: return FPFCurrency::SOS;
	case PFCurrency::SPL: return FPFCurrency::SPL;
	case PFCurrency::SRD: return FPFCurrency::SRD;
	case PFCurrency::STD: return FPFCurrency::STD;
	case PFCurrency::SVC: return FPFCurrency::SVC;
	case PFCurrency::SYP: return FPFCurrency::SYP;
	case PFCurrency::SZL: return FPFCurrency::SZL;
	case PFCurrency::THB: return FPFCurrency::THB;
	case PFCurrency::TJS: return FPFCurrency::TJS;
	case PFCurrency::TMT: return FPFCurrency::TMT;
	case PFCurrency::TND: return FPFCurrency::TND;
	case PFCurrency::TOP: return FPFCurrency::TOP;
	case PFCurrency::TRY: return FPFCurrency::TRY;
	case PFCurrency::TTD: return FPFCurrency::TTD;
	case PFCurrency::TVD: return FPFCurrency::TVD;
	case PFCurrency::TWD: return FPFCurrency::TWD;
	case PFCurrency::TZS: return FPFCurrency::TZS;
	case PFCurrency::UAH: return FPFCurrency::UAH;
	case PFCurrency::UGX: return FPFCurrency::UGX;
	case PFCurrency::USD: return FPFCurrency::USD;
	case PFCurrency::UYU: return FPFCurrency::UYU;
	case PFCurrency::UZS: return FPFCurrency::UZS;
	case PFCurrency::VEF: return FPFCurrency::VEF;
	case PFCurrency::VND: return FPFCurrency::VND;
	case PFCurrency::VUV: return FPFCurrency::VUV;
	case PFCurrency::WST: return FPFCurrency::WST;
	case PFCurrency::XAF: return FPFCurrency::XAF;
	case PFCurrency::XCD: return FPFCurrency::XCD;
	case PFCurrency::XDR: return FPFCurrency::XDR;
	case PFCurrency::XOF: return FPFCurrency::XOF;
	case PFCurrency::XPF: return FPFCurrency::XPF;
	case PFCurrency::YER: return FPFCurrency::YER;
	case PFCurrency::ZAR: return FPFCurrency::ZAR;
	case PFCurrency::ZMW: return FPFCurrency::ZMW;
	case PFCurrency::ZWD: return FPFCurrency::ZWD;
	default:
	return FPFCurrency::AED;
	}
}

const PFCurrency ConvertCurrencyToPlayfab(TSharedPtr<const FPFCurrency> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCurrency::AED;
	}

	switch(*enumVal)
	{
	case FPFCurrency::AED: return PFCurrency::AED;
	case FPFCurrency::AFN: return PFCurrency::AFN;
	case FPFCurrency::ALL: return PFCurrency::ALL;
	case FPFCurrency::AMD: return PFCurrency::AMD;
	case FPFCurrency::ANG: return PFCurrency::ANG;
	case FPFCurrency::AOA: return PFCurrency::AOA;
	case FPFCurrency::ARS: return PFCurrency::ARS;
	case FPFCurrency::AUD: return PFCurrency::AUD;
	case FPFCurrency::AWG: return PFCurrency::AWG;
	case FPFCurrency::AZN: return PFCurrency::AZN;
	case FPFCurrency::BAM: return PFCurrency::BAM;
	case FPFCurrency::BBD: return PFCurrency::BBD;
	case FPFCurrency::BDT: return PFCurrency::BDT;
	case FPFCurrency::BGN: return PFCurrency::BGN;
	case FPFCurrency::BHD: return PFCurrency::BHD;
	case FPFCurrency::BIF: return PFCurrency::BIF;
	case FPFCurrency::BMD: return PFCurrency::BMD;
	case FPFCurrency::BND: return PFCurrency::BND;
	case FPFCurrency::BOB: return PFCurrency::BOB;
	case FPFCurrency::BRL: return PFCurrency::BRL;
	case FPFCurrency::BSD: return PFCurrency::BSD;
	case FPFCurrency::BTN: return PFCurrency::BTN;
	case FPFCurrency::BWP: return PFCurrency::BWP;
	case FPFCurrency::BYR: return PFCurrency::BYR;
	case FPFCurrency::BZD: return PFCurrency::BZD;
	case FPFCurrency::CAD: return PFCurrency::CAD;
	case FPFCurrency::CDF: return PFCurrency::CDF;
	case FPFCurrency::CHF: return PFCurrency::CHF;
	case FPFCurrency::CLP: return PFCurrency::CLP;
	case FPFCurrency::CNY: return PFCurrency::CNY;
	case FPFCurrency::COP: return PFCurrency::COP;
	case FPFCurrency::CRC: return PFCurrency::CRC;
	case FPFCurrency::CUC: return PFCurrency::CUC;
	case FPFCurrency::CUP: return PFCurrency::CUP;
	case FPFCurrency::CVE: return PFCurrency::CVE;
	case FPFCurrency::CZK: return PFCurrency::CZK;
	case FPFCurrency::DJF: return PFCurrency::DJF;
	case FPFCurrency::DKK: return PFCurrency::DKK;
	case FPFCurrency::DOP: return PFCurrency::DOP;
	case FPFCurrency::DZD: return PFCurrency::DZD;
	case FPFCurrency::EGP: return PFCurrency::EGP;
	case FPFCurrency::ERN: return PFCurrency::ERN;
	case FPFCurrency::ETB: return PFCurrency::ETB;
	case FPFCurrency::EUR: return PFCurrency::EUR;
	case FPFCurrency::FJD: return PFCurrency::FJD;
	case FPFCurrency::FKP: return PFCurrency::FKP;
	case FPFCurrency::GBP: return PFCurrency::GBP;
	case FPFCurrency::GEL: return PFCurrency::GEL;
	case FPFCurrency::GGP: return PFCurrency::GGP;
	case FPFCurrency::GHS: return PFCurrency::GHS;
	case FPFCurrency::GIP: return PFCurrency::GIP;
	case FPFCurrency::GMD: return PFCurrency::GMD;
	case FPFCurrency::GNF: return PFCurrency::GNF;
	case FPFCurrency::GTQ: return PFCurrency::GTQ;
	case FPFCurrency::GYD: return PFCurrency::GYD;
	case FPFCurrency::HKD: return PFCurrency::HKD;
	case FPFCurrency::HNL: return PFCurrency::HNL;
	case FPFCurrency::HRK: return PFCurrency::HRK;
	case FPFCurrency::HTG: return PFCurrency::HTG;
	case FPFCurrency::HUF: return PFCurrency::HUF;
	case FPFCurrency::IDR: return PFCurrency::IDR;
	case FPFCurrency::ILS: return PFCurrency::ILS;
	case FPFCurrency::IMP: return PFCurrency::IMP;
	case FPFCurrency::INR: return PFCurrency::INR;
	case FPFCurrency::IQD: return PFCurrency::IQD;
	case FPFCurrency::IRR: return PFCurrency::IRR;
	case FPFCurrency::ISK: return PFCurrency::ISK;
	case FPFCurrency::JEP: return PFCurrency::JEP;
	case FPFCurrency::JMD: return PFCurrency::JMD;
	case FPFCurrency::JOD: return PFCurrency::JOD;
	case FPFCurrency::JPY: return PFCurrency::JPY;
	case FPFCurrency::KES: return PFCurrency::KES;
	case FPFCurrency::KGS: return PFCurrency::KGS;
	case FPFCurrency::KHR: return PFCurrency::KHR;
	case FPFCurrency::KMF: return PFCurrency::KMF;
	case FPFCurrency::KPW: return PFCurrency::KPW;
	case FPFCurrency::KRW: return PFCurrency::KRW;
	case FPFCurrency::KWD: return PFCurrency::KWD;
	case FPFCurrency::KYD: return PFCurrency::KYD;
	case FPFCurrency::KZT: return PFCurrency::KZT;
	case FPFCurrency::LAK: return PFCurrency::LAK;
	case FPFCurrency::LBP: return PFCurrency::LBP;
	case FPFCurrency::LKR: return PFCurrency::LKR;
	case FPFCurrency::LRD: return PFCurrency::LRD;
	case FPFCurrency::LSL: return PFCurrency::LSL;
	case FPFCurrency::LYD: return PFCurrency::LYD;
	case FPFCurrency::MAD: return PFCurrency::MAD;
	case FPFCurrency::MDL: return PFCurrency::MDL;
	case FPFCurrency::MGA: return PFCurrency::MGA;
	case FPFCurrency::MKD: return PFCurrency::MKD;
	case FPFCurrency::MMK: return PFCurrency::MMK;
	case FPFCurrency::MNT: return PFCurrency::MNT;
	case FPFCurrency::MOP: return PFCurrency::MOP;
	case FPFCurrency::MRO: return PFCurrency::MRO;
	case FPFCurrency::MUR: return PFCurrency::MUR;
	case FPFCurrency::MVR: return PFCurrency::MVR;
	case FPFCurrency::MWK: return PFCurrency::MWK;
	case FPFCurrency::MXN: return PFCurrency::MXN;
	case FPFCurrency::MYR: return PFCurrency::MYR;
	case FPFCurrency::MZN: return PFCurrency::MZN;
	case FPFCurrency::NAD: return PFCurrency::NAD;
	case FPFCurrency::NGN: return PFCurrency::NGN;
	case FPFCurrency::NIO: return PFCurrency::NIO;
	case FPFCurrency::NOK: return PFCurrency::NOK;
	case FPFCurrency::NPR: return PFCurrency::NPR;
	case FPFCurrency::NZD: return PFCurrency::NZD;
	case FPFCurrency::OMR: return PFCurrency::OMR;
	case FPFCurrency::PAB: return PFCurrency::PAB;
	case FPFCurrency::PEN: return PFCurrency::PEN;
	case FPFCurrency::PGK: return PFCurrency::PGK;
	case FPFCurrency::PHP: return PFCurrency::PHP;
	case FPFCurrency::PKR: return PFCurrency::PKR;
	case FPFCurrency::PLN: return PFCurrency::PLN;
	case FPFCurrency::PYG: return PFCurrency::PYG;
	case FPFCurrency::QAR: return PFCurrency::QAR;
	case FPFCurrency::RON: return PFCurrency::RON;
	case FPFCurrency::RSD: return PFCurrency::RSD;
	case FPFCurrency::RUB: return PFCurrency::RUB;
	case FPFCurrency::RWF: return PFCurrency::RWF;
	case FPFCurrency::SAR: return PFCurrency::SAR;
	case FPFCurrency::SBD: return PFCurrency::SBD;
	case FPFCurrency::SCR: return PFCurrency::SCR;
	case FPFCurrency::SDG: return PFCurrency::SDG;
	case FPFCurrency::SEK: return PFCurrency::SEK;
	case FPFCurrency::SGD: return PFCurrency::SGD;
	case FPFCurrency::SHP: return PFCurrency::SHP;
	case FPFCurrency::SLL: return PFCurrency::SLL;
	case FPFCurrency::SOS: return PFCurrency::SOS;
	case FPFCurrency::SPL: return PFCurrency::SPL;
	case FPFCurrency::SRD: return PFCurrency::SRD;
	case FPFCurrency::STD: return PFCurrency::STD;
	case FPFCurrency::SVC: return PFCurrency::SVC;
	case FPFCurrency::SYP: return PFCurrency::SYP;
	case FPFCurrency::SZL: return PFCurrency::SZL;
	case FPFCurrency::THB: return PFCurrency::THB;
	case FPFCurrency::TJS: return PFCurrency::TJS;
	case FPFCurrency::TMT: return PFCurrency::TMT;
	case FPFCurrency::TND: return PFCurrency::TND;
	case FPFCurrency::TOP: return PFCurrency::TOP;
	case FPFCurrency::TRY: return PFCurrency::TRY;
	case FPFCurrency::TTD: return PFCurrency::TTD;
	case FPFCurrency::TVD: return PFCurrency::TVD;
	case FPFCurrency::TWD: return PFCurrency::TWD;
	case FPFCurrency::TZS: return PFCurrency::TZS;
	case FPFCurrency::UAH: return PFCurrency::UAH;
	case FPFCurrency::UGX: return PFCurrency::UGX;
	case FPFCurrency::USD: return PFCurrency::USD;
	case FPFCurrency::UYU: return PFCurrency::UYU;
	case FPFCurrency::UZS: return PFCurrency::UZS;
	case FPFCurrency::VEF: return PFCurrency::VEF;
	case FPFCurrency::VND: return PFCurrency::VND;
	case FPFCurrency::VUV: return PFCurrency::VUV;
	case FPFCurrency::WST: return PFCurrency::WST;
	case FPFCurrency::XAF: return PFCurrency::XAF;
	case FPFCurrency::XCD: return PFCurrency::XCD;
	case FPFCurrency::XDR: return PFCurrency::XDR;
	case FPFCurrency::XOF: return PFCurrency::XOF;
	case FPFCurrency::XPF: return PFCurrency::XPF;
	case FPFCurrency::YER: return PFCurrency::YER;
	case FPFCurrency::ZAR: return PFCurrency::ZAR;
	case FPFCurrency::ZMW: return PFCurrency::ZMW;
	case FPFCurrency::ZWD: return PFCurrency::ZWD;
	default:
	return PFCurrency::AED;
	}
}

const FPFUserOrigination ConvertUserOriginationToUnreal(const PFUserOrigination* enumVal)
{
	if (enumVal == nullptr) {
		return FPFUserOrigination::Organic;
	}

	switch(*enumVal)
	{
	case PFUserOrigination::Organic: return FPFUserOrigination::Organic;
	case PFUserOrigination::Steam: return FPFUserOrigination::Steam;
	case PFUserOrigination::Google: return FPFUserOrigination::Google;
	case PFUserOrigination::Amazon: return FPFUserOrigination::Amazon;
	case PFUserOrigination::Facebook: return FPFUserOrigination::Facebook;
	case PFUserOrigination::Kongregate: return FPFUserOrigination::Kongregate;
	case PFUserOrigination::GamersFirst: return FPFUserOrigination::GamersFirst;
	case PFUserOrigination::Unknown: return FPFUserOrigination::Unknown;
	case PFUserOrigination::IOS: return FPFUserOrigination::IOS;
	case PFUserOrigination::LoadTest: return FPFUserOrigination::LoadTest;
	case PFUserOrigination::Android: return FPFUserOrigination::Android;
	case PFUserOrigination::PSN: return FPFUserOrigination::PSN;
	case PFUserOrigination::GameCenter: return FPFUserOrigination::GameCenter;
	case PFUserOrigination::CustomId: return FPFUserOrigination::CustomId;
	case PFUserOrigination::XboxLive: return FPFUserOrigination::XboxLive;
	case PFUserOrigination::Parse: return FPFUserOrigination::Parse;
	case PFUserOrigination::Twitch: return FPFUserOrigination::Twitch;
	case PFUserOrigination::ServerCustomId: return FPFUserOrigination::ServerCustomId;
	case PFUserOrigination::NintendoSwitchDeviceId: return FPFUserOrigination::NintendoSwitchDeviceId;
	case PFUserOrigination::FacebookInstantGamesId: return FPFUserOrigination::FacebookInstantGamesId;
	case PFUserOrigination::OpenIdConnect: return FPFUserOrigination::OpenIdConnect;
	case PFUserOrigination::Apple: return FPFUserOrigination::Apple;
	case PFUserOrigination::NintendoSwitchAccount: return FPFUserOrigination::NintendoSwitchAccount;
	case PFUserOrigination::GooglePlayGames: return FPFUserOrigination::GooglePlayGames;
	case PFUserOrigination::XboxMobileStore: return FPFUserOrigination::XboxMobileStore;
	case PFUserOrigination::King: return FPFUserOrigination::King;
	case PFUserOrigination::BattleNet: return FPFUserOrigination::BattleNet;
	default:
	return FPFUserOrigination::Organic;
	}
}

const PFUserOrigination ConvertUserOriginationToPlayfab(TSharedPtr<const FPFUserOrigination> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFUserOrigination::Organic;
	}

	switch(*enumVal)
	{
	case FPFUserOrigination::Organic: return PFUserOrigination::Organic;
	case FPFUserOrigination::Steam: return PFUserOrigination::Steam;
	case FPFUserOrigination::Google: return PFUserOrigination::Google;
	case FPFUserOrigination::Amazon: return PFUserOrigination::Amazon;
	case FPFUserOrigination::Facebook: return PFUserOrigination::Facebook;
	case FPFUserOrigination::Kongregate: return PFUserOrigination::Kongregate;
	case FPFUserOrigination::GamersFirst: return PFUserOrigination::GamersFirst;
	case FPFUserOrigination::Unknown: return PFUserOrigination::Unknown;
	case FPFUserOrigination::IOS: return PFUserOrigination::IOS;
	case FPFUserOrigination::LoadTest: return PFUserOrigination::LoadTest;
	case FPFUserOrigination::Android: return PFUserOrigination::Android;
	case FPFUserOrigination::PSN: return PFUserOrigination::PSN;
	case FPFUserOrigination::GameCenter: return PFUserOrigination::GameCenter;
	case FPFUserOrigination::CustomId: return PFUserOrigination::CustomId;
	case FPFUserOrigination::XboxLive: return PFUserOrigination::XboxLive;
	case FPFUserOrigination::Parse: return PFUserOrigination::Parse;
	case FPFUserOrigination::Twitch: return PFUserOrigination::Twitch;
	case FPFUserOrigination::ServerCustomId: return PFUserOrigination::ServerCustomId;
	case FPFUserOrigination::NintendoSwitchDeviceId: return PFUserOrigination::NintendoSwitchDeviceId;
	case FPFUserOrigination::FacebookInstantGamesId: return PFUserOrigination::FacebookInstantGamesId;
	case FPFUserOrigination::OpenIdConnect: return PFUserOrigination::OpenIdConnect;
	case FPFUserOrigination::Apple: return PFUserOrigination::Apple;
	case FPFUserOrigination::NintendoSwitchAccount: return PFUserOrigination::NintendoSwitchAccount;
	case FPFUserOrigination::GooglePlayGames: return PFUserOrigination::GooglePlayGames;
	case FPFUserOrigination::XboxMobileStore: return PFUserOrigination::XboxMobileStore;
	case FPFUserOrigination::King: return PFUserOrigination::King;
	case FPFUserOrigination::BattleNet: return PFUserOrigination::BattleNet;
	default:
	return PFUserOrigination::Organic;
	}
}

const FPFUserDataPermission ConvertUserDataPermissionToUnreal(const PFUserDataPermission* enumVal)
{
	if (enumVal == nullptr) {
		return FPFUserDataPermission::Private;
	}

	switch(*enumVal)
	{
	case PFUserDataPermission::Private: return FPFUserDataPermission::Private;
	case PFUserDataPermission::Public: return FPFUserDataPermission::Public;
	default:
	return FPFUserDataPermission::Private;
	}
}

const PFUserDataPermission ConvertUserDataPermissionToPlayfab(TSharedPtr<const FPFUserDataPermission> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFUserDataPermission::Private;
	}

	switch(*enumVal)
	{
	case FPFUserDataPermission::Private: return PFUserDataPermission::Private;
	case FPFUserDataPermission::Public: return PFUserDataPermission::Public;
	default:
	return PFUserDataPermission::Private;
	}
}

const FPFEmailVerificationStatus ConvertEmailVerificationStatusToUnreal(const PFEmailVerificationStatus* enumVal)
{
	if (enumVal == nullptr) {
		return FPFEmailVerificationStatus::Unverified;
	}

	switch(*enumVal)
	{
	case PFEmailVerificationStatus::Unverified: return FPFEmailVerificationStatus::Unverified;
	case PFEmailVerificationStatus::Pending: return FPFEmailVerificationStatus::Pending;
	case PFEmailVerificationStatus::Confirmed: return FPFEmailVerificationStatus::Confirmed;
	default:
	return FPFEmailVerificationStatus::Unverified;
	}
}

const PFEmailVerificationStatus ConvertEmailVerificationStatusToPlayfab(TSharedPtr<const FPFEmailVerificationStatus> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFEmailVerificationStatus::Unverified;
	}

	switch(*enumVal)
	{
	case FPFEmailVerificationStatus::Unverified: return PFEmailVerificationStatus::Unverified;
	case FPFEmailVerificationStatus::Pending: return PFEmailVerificationStatus::Pending;
	case FPFEmailVerificationStatus::Confirmed: return PFEmailVerificationStatus::Confirmed;
	default:
	return PFEmailVerificationStatus::Unverified;
	}
}

const FPFLoginIdentityProvider ConvertLoginIdentityProviderToUnreal(const PFLoginIdentityProvider* enumVal)
{
	if (enumVal == nullptr) {
		return FPFLoginIdentityProvider::Unknown;
	}

	switch(*enumVal)
	{
	case PFLoginIdentityProvider::Unknown: return FPFLoginIdentityProvider::Unknown;
	case PFLoginIdentityProvider::PlayFab: return FPFLoginIdentityProvider::PlayFab;
	case PFLoginIdentityProvider::Custom: return FPFLoginIdentityProvider::Custom;
	case PFLoginIdentityProvider::GameCenter: return FPFLoginIdentityProvider::GameCenter;
	case PFLoginIdentityProvider::GooglePlay: return FPFLoginIdentityProvider::GooglePlay;
	case PFLoginIdentityProvider::Steam: return FPFLoginIdentityProvider::Steam;
	case PFLoginIdentityProvider::XBoxLive: return FPFLoginIdentityProvider::XBoxLive;
	case PFLoginIdentityProvider::PSN: return FPFLoginIdentityProvider::PSN;
	case PFLoginIdentityProvider::Kongregate: return FPFLoginIdentityProvider::Kongregate;
	case PFLoginIdentityProvider::Facebook: return FPFLoginIdentityProvider::Facebook;
	case PFLoginIdentityProvider::IOSDevice: return FPFLoginIdentityProvider::IOSDevice;
	case PFLoginIdentityProvider::AndroidDevice: return FPFLoginIdentityProvider::AndroidDevice;
	case PFLoginIdentityProvider::Twitch: return FPFLoginIdentityProvider::Twitch;
	case PFLoginIdentityProvider::WindowsHello: return FPFLoginIdentityProvider::WindowsHello;
	case PFLoginIdentityProvider::GameServer: return FPFLoginIdentityProvider::GameServer;
	case PFLoginIdentityProvider::CustomServer: return FPFLoginIdentityProvider::CustomServer;
	case PFLoginIdentityProvider::NintendoSwitch: return FPFLoginIdentityProvider::NintendoSwitch;
	case PFLoginIdentityProvider::FacebookInstantGames: return FPFLoginIdentityProvider::FacebookInstantGames;
	case PFLoginIdentityProvider::OpenIdConnect: return FPFLoginIdentityProvider::OpenIdConnect;
	case PFLoginIdentityProvider::Apple: return FPFLoginIdentityProvider::Apple;
	case PFLoginIdentityProvider::NintendoSwitchAccount: return FPFLoginIdentityProvider::NintendoSwitchAccount;
	case PFLoginIdentityProvider::GooglePlayGames: return FPFLoginIdentityProvider::GooglePlayGames;
	case PFLoginIdentityProvider::XboxMobileStore: return FPFLoginIdentityProvider::XboxMobileStore;
	case PFLoginIdentityProvider::King: return FPFLoginIdentityProvider::King;
	case PFLoginIdentityProvider::BattleNet: return FPFLoginIdentityProvider::BattleNet;
	default:
	return FPFLoginIdentityProvider::Unknown;
	}
}

const PFLoginIdentityProvider ConvertLoginIdentityProviderToPlayfab(TSharedPtr<const FPFLoginIdentityProvider> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFLoginIdentityProvider::Unknown;
	}

	switch(*enumVal)
	{
	case FPFLoginIdentityProvider::Unknown: return PFLoginIdentityProvider::Unknown;
	case FPFLoginIdentityProvider::PlayFab: return PFLoginIdentityProvider::PlayFab;
	case FPFLoginIdentityProvider::Custom: return PFLoginIdentityProvider::Custom;
	case FPFLoginIdentityProvider::GameCenter: return PFLoginIdentityProvider::GameCenter;
	case FPFLoginIdentityProvider::GooglePlay: return PFLoginIdentityProvider::GooglePlay;
	case FPFLoginIdentityProvider::Steam: return PFLoginIdentityProvider::Steam;
	case FPFLoginIdentityProvider::XBoxLive: return PFLoginIdentityProvider::XBoxLive;
	case FPFLoginIdentityProvider::PSN: return PFLoginIdentityProvider::PSN;
	case FPFLoginIdentityProvider::Kongregate: return PFLoginIdentityProvider::Kongregate;
	case FPFLoginIdentityProvider::Facebook: return PFLoginIdentityProvider::Facebook;
	case FPFLoginIdentityProvider::IOSDevice: return PFLoginIdentityProvider::IOSDevice;
	case FPFLoginIdentityProvider::AndroidDevice: return PFLoginIdentityProvider::AndroidDevice;
	case FPFLoginIdentityProvider::Twitch: return PFLoginIdentityProvider::Twitch;
	case FPFLoginIdentityProvider::WindowsHello: return PFLoginIdentityProvider::WindowsHello;
	case FPFLoginIdentityProvider::GameServer: return PFLoginIdentityProvider::GameServer;
	case FPFLoginIdentityProvider::CustomServer: return PFLoginIdentityProvider::CustomServer;
	case FPFLoginIdentityProvider::NintendoSwitch: return PFLoginIdentityProvider::NintendoSwitch;
	case FPFLoginIdentityProvider::FacebookInstantGames: return PFLoginIdentityProvider::FacebookInstantGames;
	case FPFLoginIdentityProvider::OpenIdConnect: return PFLoginIdentityProvider::OpenIdConnect;
	case FPFLoginIdentityProvider::Apple: return PFLoginIdentityProvider::Apple;
	case FPFLoginIdentityProvider::NintendoSwitchAccount: return PFLoginIdentityProvider::NintendoSwitchAccount;
	case FPFLoginIdentityProvider::GooglePlayGames: return PFLoginIdentityProvider::GooglePlayGames;
	case FPFLoginIdentityProvider::XboxMobileStore: return PFLoginIdentityProvider::XboxMobileStore;
	case FPFLoginIdentityProvider::King: return PFLoginIdentityProvider::King;
	case FPFLoginIdentityProvider::BattleNet: return PFLoginIdentityProvider::BattleNet;
	default:
	return PFLoginIdentityProvider::Unknown;
	}
}

const FPFContinentCode ConvertContinentCodeToUnreal(const PFContinentCode* enumVal)
{
	if (enumVal == nullptr) {
		return FPFContinentCode::AF;
	}

	switch(*enumVal)
	{
	case PFContinentCode::AF: return FPFContinentCode::AF;
	case PFContinentCode::AN: return FPFContinentCode::AN;
	case PFContinentCode::AS: return FPFContinentCode::AS;
	case PFContinentCode::EU: return FPFContinentCode::EU;
	case PFContinentCode::NA: return FPFContinentCode::NA;
	case PFContinentCode::OC: return FPFContinentCode::OC;
	case PFContinentCode::SA: return FPFContinentCode::SA;
	case PFContinentCode::Unknown: return FPFContinentCode::Unknown;
	default:
	return FPFContinentCode::AF;
	}
}

const PFContinentCode ConvertContinentCodeToPlayfab(TSharedPtr<const FPFContinentCode> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFContinentCode::AF;
	}

	switch(*enumVal)
	{
	case FPFContinentCode::AF: return PFContinentCode::AF;
	case FPFContinentCode::AN: return PFContinentCode::AN;
	case FPFContinentCode::AS: return PFContinentCode::AS;
	case FPFContinentCode::EU: return PFContinentCode::EU;
	case FPFContinentCode::NA: return PFContinentCode::NA;
	case FPFContinentCode::OC: return PFContinentCode::OC;
	case FPFContinentCode::SA: return PFContinentCode::SA;
	case FPFContinentCode::Unknown: return PFContinentCode::Unknown;
	default:
	return PFContinentCode::AF;
	}
}

const FPFCountryCode ConvertCountryCodeToUnreal(const PFCountryCode* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCountryCode::AF;
	}

	switch(*enumVal)
	{
	case PFCountryCode::AF: return FPFCountryCode::AF;
	case PFCountryCode::AX: return FPFCountryCode::AX;
	case PFCountryCode::AL: return FPFCountryCode::AL;
	case PFCountryCode::DZ: return FPFCountryCode::DZ;
	case PFCountryCode::AS: return FPFCountryCode::AS;
	case PFCountryCode::AD: return FPFCountryCode::AD;
	case PFCountryCode::AO: return FPFCountryCode::AO;
	case PFCountryCode::AI: return FPFCountryCode::AI;
	case PFCountryCode::AQ: return FPFCountryCode::AQ;
	case PFCountryCode::AG: return FPFCountryCode::AG;
	case PFCountryCode::AR: return FPFCountryCode::AR;
	case PFCountryCode::AM: return FPFCountryCode::AM;
	case PFCountryCode::AW: return FPFCountryCode::AW;
	case PFCountryCode::AU: return FPFCountryCode::AU;
	case PFCountryCode::AT: return FPFCountryCode::AT;
	case PFCountryCode::AZ: return FPFCountryCode::AZ;
	case PFCountryCode::BS: return FPFCountryCode::BS;
	case PFCountryCode::BH: return FPFCountryCode::BH;
	case PFCountryCode::BD: return FPFCountryCode::BD;
	case PFCountryCode::BB: return FPFCountryCode::BB;
	case PFCountryCode::BY: return FPFCountryCode::BY;
	case PFCountryCode::BE: return FPFCountryCode::BE;
	case PFCountryCode::BZ: return FPFCountryCode::BZ;
	case PFCountryCode::BJ: return FPFCountryCode::BJ;
	case PFCountryCode::BM: return FPFCountryCode::BM;
	case PFCountryCode::BT: return FPFCountryCode::BT;
	case PFCountryCode::BO: return FPFCountryCode::BO;
	case PFCountryCode::BQ: return FPFCountryCode::BQ;
	case PFCountryCode::BA: return FPFCountryCode::BA;
	case PFCountryCode::BW: return FPFCountryCode::BW;
	case PFCountryCode::BV: return FPFCountryCode::BV;
	case PFCountryCode::BR: return FPFCountryCode::BR;
	case PFCountryCode::IO: return FPFCountryCode::IO;
	case PFCountryCode::BN: return FPFCountryCode::BN;
	case PFCountryCode::BG: return FPFCountryCode::BG;
	case PFCountryCode::BF: return FPFCountryCode::BF;
	case PFCountryCode::BI: return FPFCountryCode::BI;
	case PFCountryCode::KH: return FPFCountryCode::KH;
	case PFCountryCode::CM: return FPFCountryCode::CM;
	case PFCountryCode::CA: return FPFCountryCode::CA;
	case PFCountryCode::CV: return FPFCountryCode::CV;
	case PFCountryCode::KY: return FPFCountryCode::KY;
	case PFCountryCode::CF: return FPFCountryCode::CF;
	case PFCountryCode::TD: return FPFCountryCode::TD;
	case PFCountryCode::CL: return FPFCountryCode::CL;
	case PFCountryCode::CN: return FPFCountryCode::CN;
	case PFCountryCode::CX: return FPFCountryCode::CX;
	case PFCountryCode::CC: return FPFCountryCode::CC;
	case PFCountryCode::CO: return FPFCountryCode::CO;
	case PFCountryCode::KM: return FPFCountryCode::KM;
	case PFCountryCode::CG: return FPFCountryCode::CG;
	case PFCountryCode::CD: return FPFCountryCode::CD;
	case PFCountryCode::CK: return FPFCountryCode::CK;
	case PFCountryCode::CR: return FPFCountryCode::CR;
	case PFCountryCode::CI: return FPFCountryCode::CI;
	case PFCountryCode::HR: return FPFCountryCode::HR;
	case PFCountryCode::CU: return FPFCountryCode::CU;
	case PFCountryCode::CW: return FPFCountryCode::CW;
	case PFCountryCode::CY: return FPFCountryCode::CY;
	case PFCountryCode::CZ: return FPFCountryCode::CZ;
	case PFCountryCode::DK: return FPFCountryCode::DK;
	case PFCountryCode::DJ: return FPFCountryCode::DJ;
	case PFCountryCode::DM: return FPFCountryCode::DM;
	case PFCountryCode::DO: return FPFCountryCode::DO;
	case PFCountryCode::EC: return FPFCountryCode::EC;
	case PFCountryCode::EG: return FPFCountryCode::EG;
	case PFCountryCode::SV: return FPFCountryCode::SV;
	case PFCountryCode::GQ: return FPFCountryCode::GQ;
	case PFCountryCode::ER: return FPFCountryCode::ER;
	case PFCountryCode::EE: return FPFCountryCode::EE;
	case PFCountryCode::ET: return FPFCountryCode::ET;
	case PFCountryCode::FK: return FPFCountryCode::FK;
	case PFCountryCode::FO: return FPFCountryCode::FO;
	case PFCountryCode::FJ: return FPFCountryCode::FJ;
	case PFCountryCode::FI: return FPFCountryCode::FI;
	case PFCountryCode::FR: return FPFCountryCode::FR;
	case PFCountryCode::GF: return FPFCountryCode::GF;
	case PFCountryCode::PF: return FPFCountryCode::PF;
	case PFCountryCode::TF: return FPFCountryCode::TF;
	case PFCountryCode::GA: return FPFCountryCode::GA;
	case PFCountryCode::GM: return FPFCountryCode::GM;
	case PFCountryCode::GE: return FPFCountryCode::GE;
	case PFCountryCode::DE: return FPFCountryCode::DE;
	case PFCountryCode::GH: return FPFCountryCode::GH;
	case PFCountryCode::GI: return FPFCountryCode::GI;
	case PFCountryCode::GR: return FPFCountryCode::GR;
	case PFCountryCode::GL: return FPFCountryCode::GL;
	case PFCountryCode::GD: return FPFCountryCode::GD;
	case PFCountryCode::GP: return FPFCountryCode::GP;
	case PFCountryCode::GU: return FPFCountryCode::GU;
	case PFCountryCode::GT: return FPFCountryCode::GT;
	case PFCountryCode::GG: return FPFCountryCode::GG;
	case PFCountryCode::GN: return FPFCountryCode::GN;
	case PFCountryCode::GW: return FPFCountryCode::GW;
	case PFCountryCode::GY: return FPFCountryCode::GY;
	case PFCountryCode::HT: return FPFCountryCode::HT;
	case PFCountryCode::HM: return FPFCountryCode::HM;
	case PFCountryCode::VA: return FPFCountryCode::VA;
	case PFCountryCode::HN: return FPFCountryCode::HN;
	case PFCountryCode::HK: return FPFCountryCode::HK;
	case PFCountryCode::HU: return FPFCountryCode::HU;
	case PFCountryCode::IS: return FPFCountryCode::IS;
	case PFCountryCode::IN: return FPFCountryCode::IN;
	case PFCountryCode::ID: return FPFCountryCode::ID;
	case PFCountryCode::IR: return FPFCountryCode::IR;
	case PFCountryCode::IQ: return FPFCountryCode::IQ;
	case PFCountryCode::IE: return FPFCountryCode::IE;
	case PFCountryCode::IM: return FPFCountryCode::IM;
	case PFCountryCode::IL: return FPFCountryCode::IL;
	case PFCountryCode::IT: return FPFCountryCode::IT;
	case PFCountryCode::JM: return FPFCountryCode::JM;
	case PFCountryCode::JP: return FPFCountryCode::JP;
	case PFCountryCode::JE: return FPFCountryCode::JE;
	case PFCountryCode::JO: return FPFCountryCode::JO;
	case PFCountryCode::KZ: return FPFCountryCode::KZ;
	case PFCountryCode::KE: return FPFCountryCode::KE;
	case PFCountryCode::KI: return FPFCountryCode::KI;
	case PFCountryCode::KP: return FPFCountryCode::KP;
	case PFCountryCode::KR: return FPFCountryCode::KR;
	case PFCountryCode::KW: return FPFCountryCode::KW;
	case PFCountryCode::KG: return FPFCountryCode::KG;
	case PFCountryCode::LA: return FPFCountryCode::LA;
	case PFCountryCode::LV: return FPFCountryCode::LV;
	case PFCountryCode::LB: return FPFCountryCode::LB;
	case PFCountryCode::LS: return FPFCountryCode::LS;
	case PFCountryCode::LR: return FPFCountryCode::LR;
	case PFCountryCode::LY: return FPFCountryCode::LY;
	case PFCountryCode::LI: return FPFCountryCode::LI;
	case PFCountryCode::LT: return FPFCountryCode::LT;
	case PFCountryCode::LU: return FPFCountryCode::LU;
	case PFCountryCode::MO: return FPFCountryCode::MO;
	case PFCountryCode::MK: return FPFCountryCode::MK;
	case PFCountryCode::MG: return FPFCountryCode::MG;
	case PFCountryCode::MW: return FPFCountryCode::MW;
	case PFCountryCode::MY: return FPFCountryCode::MY;
	case PFCountryCode::MV: return FPFCountryCode::MV;
	case PFCountryCode::ML: return FPFCountryCode::ML;
	case PFCountryCode::MT: return FPFCountryCode::MT;
	case PFCountryCode::MH: return FPFCountryCode::MH;
	case PFCountryCode::MQ: return FPFCountryCode::MQ;
	case PFCountryCode::MR: return FPFCountryCode::MR;
	case PFCountryCode::MU: return FPFCountryCode::MU;
	case PFCountryCode::YT: return FPFCountryCode::YT;
	case PFCountryCode::MX: return FPFCountryCode::MX;
	case PFCountryCode::FM: return FPFCountryCode::FM;
	case PFCountryCode::MD: return FPFCountryCode::MD;
	case PFCountryCode::MC: return FPFCountryCode::MC;
	case PFCountryCode::MN: return FPFCountryCode::MN;
	case PFCountryCode::ME: return FPFCountryCode::ME;
	case PFCountryCode::MS: return FPFCountryCode::MS;
	case PFCountryCode::MA: return FPFCountryCode::MA;
	case PFCountryCode::MZ: return FPFCountryCode::MZ;
	case PFCountryCode::MM: return FPFCountryCode::MM;
	case PFCountryCode::NA: return FPFCountryCode::NA;
	case PFCountryCode::NR: return FPFCountryCode::NR;
	case PFCountryCode::NP: return FPFCountryCode::NP;
	case PFCountryCode::NL: return FPFCountryCode::NL;
	case PFCountryCode::NC: return FPFCountryCode::NC;
	case PFCountryCode::NZ: return FPFCountryCode::NZ;
	case PFCountryCode::NI: return FPFCountryCode::NI;
	case PFCountryCode::NE: return FPFCountryCode::NE;
	case PFCountryCode::NG: return FPFCountryCode::NG;
	case PFCountryCode::NU: return FPFCountryCode::NU;
	case PFCountryCode::NF: return FPFCountryCode::NF;
	case PFCountryCode::MP: return FPFCountryCode::MP;
	case PFCountryCode::NO: return FPFCountryCode::NO;
	case PFCountryCode::OM: return FPFCountryCode::OM;
	case PFCountryCode::PK: return FPFCountryCode::PK;
	case PFCountryCode::PW: return FPFCountryCode::PW;
	case PFCountryCode::PS: return FPFCountryCode::PS;
	case PFCountryCode::PA: return FPFCountryCode::PA;
	case PFCountryCode::PG: return FPFCountryCode::PG;
	case PFCountryCode::PY: return FPFCountryCode::PY;
	case PFCountryCode::PE: return FPFCountryCode::PE;
	case PFCountryCode::PH: return FPFCountryCode::PH;
	case PFCountryCode::PN: return FPFCountryCode::PN;
	case PFCountryCode::PL: return FPFCountryCode::PL;
	case PFCountryCode::PT: return FPFCountryCode::PT;
	case PFCountryCode::PR: return FPFCountryCode::PR;
	case PFCountryCode::QA: return FPFCountryCode::QA;
	case PFCountryCode::RE: return FPFCountryCode::RE;
	case PFCountryCode::RO: return FPFCountryCode::RO;
	case PFCountryCode::RU: return FPFCountryCode::RU;
	case PFCountryCode::RW: return FPFCountryCode::RW;
	case PFCountryCode::BL: return FPFCountryCode::BL;
	case PFCountryCode::SH: return FPFCountryCode::SH;
	case PFCountryCode::KN: return FPFCountryCode::KN;
	case PFCountryCode::LC: return FPFCountryCode::LC;
	case PFCountryCode::MF: return FPFCountryCode::MF;
	case PFCountryCode::PM: return FPFCountryCode::PM;
	case PFCountryCode::VC: return FPFCountryCode::VC;
	case PFCountryCode::WS: return FPFCountryCode::WS;
	case PFCountryCode::SM: return FPFCountryCode::SM;
	case PFCountryCode::ST: return FPFCountryCode::ST;
	case PFCountryCode::SA: return FPFCountryCode::SA;
	case PFCountryCode::SN: return FPFCountryCode::SN;
	case PFCountryCode::RS: return FPFCountryCode::RS;
	case PFCountryCode::SC: return FPFCountryCode::SC;
	case PFCountryCode::SL: return FPFCountryCode::SL;
	case PFCountryCode::SG: return FPFCountryCode::SG;
	case PFCountryCode::SX: return FPFCountryCode::SX;
	case PFCountryCode::SK: return FPFCountryCode::SK;
	case PFCountryCode::SI: return FPFCountryCode::SI;
	case PFCountryCode::SB: return FPFCountryCode::SB;
	case PFCountryCode::SO: return FPFCountryCode::SO;
	case PFCountryCode::ZA: return FPFCountryCode::ZA;
	case PFCountryCode::GS: return FPFCountryCode::GS;
	case PFCountryCode::SS: return FPFCountryCode::SS;
	case PFCountryCode::ES: return FPFCountryCode::ES;
	case PFCountryCode::LK: return FPFCountryCode::LK;
	case PFCountryCode::SD: return FPFCountryCode::SD;
	case PFCountryCode::SR: return FPFCountryCode::SR;
	case PFCountryCode::SJ: return FPFCountryCode::SJ;
	case PFCountryCode::SZ: return FPFCountryCode::SZ;
	case PFCountryCode::SE: return FPFCountryCode::SE;
	case PFCountryCode::CH: return FPFCountryCode::CH;
	case PFCountryCode::SY: return FPFCountryCode::SY;
	case PFCountryCode::TW: return FPFCountryCode::TW;
	case PFCountryCode::TJ: return FPFCountryCode::TJ;
	case PFCountryCode::TZ: return FPFCountryCode::TZ;
	case PFCountryCode::TH: return FPFCountryCode::TH;
	case PFCountryCode::TL: return FPFCountryCode::TL;
	case PFCountryCode::TG: return FPFCountryCode::TG;
	case PFCountryCode::TK: return FPFCountryCode::TK;
	case PFCountryCode::TO: return FPFCountryCode::TO;
	case PFCountryCode::TT: return FPFCountryCode::TT;
	case PFCountryCode::TN: return FPFCountryCode::TN;
	case PFCountryCode::TR: return FPFCountryCode::TR;
	case PFCountryCode::TM: return FPFCountryCode::TM;
	case PFCountryCode::TC: return FPFCountryCode::TC;
	case PFCountryCode::TV: return FPFCountryCode::TV;
	case PFCountryCode::UG: return FPFCountryCode::UG;
	case PFCountryCode::UA: return FPFCountryCode::UA;
	case PFCountryCode::AE: return FPFCountryCode::AE;
	case PFCountryCode::GB: return FPFCountryCode::GB;
	case PFCountryCode::US: return FPFCountryCode::US;
	case PFCountryCode::UM: return FPFCountryCode::UM;
	case PFCountryCode::UY: return FPFCountryCode::UY;
	case PFCountryCode::UZ: return FPFCountryCode::UZ;
	case PFCountryCode::VU: return FPFCountryCode::VU;
	case PFCountryCode::VE: return FPFCountryCode::VE;
	case PFCountryCode::VN: return FPFCountryCode::VN;
	case PFCountryCode::VG: return FPFCountryCode::VG;
	case PFCountryCode::VI: return FPFCountryCode::VI;
	case PFCountryCode::WF: return FPFCountryCode::WF;
	case PFCountryCode::EH: return FPFCountryCode::EH;
	case PFCountryCode::YE: return FPFCountryCode::YE;
	case PFCountryCode::ZM: return FPFCountryCode::ZM;
	case PFCountryCode::ZW: return FPFCountryCode::ZW;
	case PFCountryCode::Unknown: return FPFCountryCode::Unknown;
	default:
	return FPFCountryCode::AF;
	}
}

const PFCountryCode ConvertCountryCodeToPlayfab(TSharedPtr<const FPFCountryCode> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCountryCode::AF;
	}

	switch(*enumVal)
	{
	case FPFCountryCode::AF: return PFCountryCode::AF;
	case FPFCountryCode::AX: return PFCountryCode::AX;
	case FPFCountryCode::AL: return PFCountryCode::AL;
	case FPFCountryCode::DZ: return PFCountryCode::DZ;
	case FPFCountryCode::AS: return PFCountryCode::AS;
	case FPFCountryCode::AD: return PFCountryCode::AD;
	case FPFCountryCode::AO: return PFCountryCode::AO;
	case FPFCountryCode::AI: return PFCountryCode::AI;
	case FPFCountryCode::AQ: return PFCountryCode::AQ;
	case FPFCountryCode::AG: return PFCountryCode::AG;
	case FPFCountryCode::AR: return PFCountryCode::AR;
	case FPFCountryCode::AM: return PFCountryCode::AM;
	case FPFCountryCode::AW: return PFCountryCode::AW;
	case FPFCountryCode::AU: return PFCountryCode::AU;
	case FPFCountryCode::AT: return PFCountryCode::AT;
	case FPFCountryCode::AZ: return PFCountryCode::AZ;
	case FPFCountryCode::BS: return PFCountryCode::BS;
	case FPFCountryCode::BH: return PFCountryCode::BH;
	case FPFCountryCode::BD: return PFCountryCode::BD;
	case FPFCountryCode::BB: return PFCountryCode::BB;
	case FPFCountryCode::BY: return PFCountryCode::BY;
	case FPFCountryCode::BE: return PFCountryCode::BE;
	case FPFCountryCode::BZ: return PFCountryCode::BZ;
	case FPFCountryCode::BJ: return PFCountryCode::BJ;
	case FPFCountryCode::BM: return PFCountryCode::BM;
	case FPFCountryCode::BT: return PFCountryCode::BT;
	case FPFCountryCode::BO: return PFCountryCode::BO;
	case FPFCountryCode::BQ: return PFCountryCode::BQ;
	case FPFCountryCode::BA: return PFCountryCode::BA;
	case FPFCountryCode::BW: return PFCountryCode::BW;
	case FPFCountryCode::BV: return PFCountryCode::BV;
	case FPFCountryCode::BR: return PFCountryCode::BR;
	case FPFCountryCode::IO: return PFCountryCode::IO;
	case FPFCountryCode::BN: return PFCountryCode::BN;
	case FPFCountryCode::BG: return PFCountryCode::BG;
	case FPFCountryCode::BF: return PFCountryCode::BF;
	case FPFCountryCode::BI: return PFCountryCode::BI;
	case FPFCountryCode::KH: return PFCountryCode::KH;
	case FPFCountryCode::CM: return PFCountryCode::CM;
	case FPFCountryCode::CA: return PFCountryCode::CA;
	case FPFCountryCode::CV: return PFCountryCode::CV;
	case FPFCountryCode::KY: return PFCountryCode::KY;
	case FPFCountryCode::CF: return PFCountryCode::CF;
	case FPFCountryCode::TD: return PFCountryCode::TD;
	case FPFCountryCode::CL: return PFCountryCode::CL;
	case FPFCountryCode::CN: return PFCountryCode::CN;
	case FPFCountryCode::CX: return PFCountryCode::CX;
	case FPFCountryCode::CC: return PFCountryCode::CC;
	case FPFCountryCode::CO: return PFCountryCode::CO;
	case FPFCountryCode::KM: return PFCountryCode::KM;
	case FPFCountryCode::CG: return PFCountryCode::CG;
	case FPFCountryCode::CD: return PFCountryCode::CD;
	case FPFCountryCode::CK: return PFCountryCode::CK;
	case FPFCountryCode::CR: return PFCountryCode::CR;
	case FPFCountryCode::CI: return PFCountryCode::CI;
	case FPFCountryCode::HR: return PFCountryCode::HR;
	case FPFCountryCode::CU: return PFCountryCode::CU;
	case FPFCountryCode::CW: return PFCountryCode::CW;
	case FPFCountryCode::CY: return PFCountryCode::CY;
	case FPFCountryCode::CZ: return PFCountryCode::CZ;
	case FPFCountryCode::DK: return PFCountryCode::DK;
	case FPFCountryCode::DJ: return PFCountryCode::DJ;
	case FPFCountryCode::DM: return PFCountryCode::DM;
	case FPFCountryCode::DO: return PFCountryCode::DO;
	case FPFCountryCode::EC: return PFCountryCode::EC;
	case FPFCountryCode::EG: return PFCountryCode::EG;
	case FPFCountryCode::SV: return PFCountryCode::SV;
	case FPFCountryCode::GQ: return PFCountryCode::GQ;
	case FPFCountryCode::ER: return PFCountryCode::ER;
	case FPFCountryCode::EE: return PFCountryCode::EE;
	case FPFCountryCode::ET: return PFCountryCode::ET;
	case FPFCountryCode::FK: return PFCountryCode::FK;
	case FPFCountryCode::FO: return PFCountryCode::FO;
	case FPFCountryCode::FJ: return PFCountryCode::FJ;
	case FPFCountryCode::FI: return PFCountryCode::FI;
	case FPFCountryCode::FR: return PFCountryCode::FR;
	case FPFCountryCode::GF: return PFCountryCode::GF;
	case FPFCountryCode::PF: return PFCountryCode::PF;
	case FPFCountryCode::TF: return PFCountryCode::TF;
	case FPFCountryCode::GA: return PFCountryCode::GA;
	case FPFCountryCode::GM: return PFCountryCode::GM;
	case FPFCountryCode::GE: return PFCountryCode::GE;
	case FPFCountryCode::DE: return PFCountryCode::DE;
	case FPFCountryCode::GH: return PFCountryCode::GH;
	case FPFCountryCode::GI: return PFCountryCode::GI;
	case FPFCountryCode::GR: return PFCountryCode::GR;
	case FPFCountryCode::GL: return PFCountryCode::GL;
	case FPFCountryCode::GD: return PFCountryCode::GD;
	case FPFCountryCode::GP: return PFCountryCode::GP;
	case FPFCountryCode::GU: return PFCountryCode::GU;
	case FPFCountryCode::GT: return PFCountryCode::GT;
	case FPFCountryCode::GG: return PFCountryCode::GG;
	case FPFCountryCode::GN: return PFCountryCode::GN;
	case FPFCountryCode::GW: return PFCountryCode::GW;
	case FPFCountryCode::GY: return PFCountryCode::GY;
	case FPFCountryCode::HT: return PFCountryCode::HT;
	case FPFCountryCode::HM: return PFCountryCode::HM;
	case FPFCountryCode::VA: return PFCountryCode::VA;
	case FPFCountryCode::HN: return PFCountryCode::HN;
	case FPFCountryCode::HK: return PFCountryCode::HK;
	case FPFCountryCode::HU: return PFCountryCode::HU;
	case FPFCountryCode::IS: return PFCountryCode::IS;
	case FPFCountryCode::IN: return PFCountryCode::IN;
	case FPFCountryCode::ID: return PFCountryCode::ID;
	case FPFCountryCode::IR: return PFCountryCode::IR;
	case FPFCountryCode::IQ: return PFCountryCode::IQ;
	case FPFCountryCode::IE: return PFCountryCode::IE;
	case FPFCountryCode::IM: return PFCountryCode::IM;
	case FPFCountryCode::IL: return PFCountryCode::IL;
	case FPFCountryCode::IT: return PFCountryCode::IT;
	case FPFCountryCode::JM: return PFCountryCode::JM;
	case FPFCountryCode::JP: return PFCountryCode::JP;
	case FPFCountryCode::JE: return PFCountryCode::JE;
	case FPFCountryCode::JO: return PFCountryCode::JO;
	case FPFCountryCode::KZ: return PFCountryCode::KZ;
	case FPFCountryCode::KE: return PFCountryCode::KE;
	case FPFCountryCode::KI: return PFCountryCode::KI;
	case FPFCountryCode::KP: return PFCountryCode::KP;
	case FPFCountryCode::KR: return PFCountryCode::KR;
	case FPFCountryCode::KW: return PFCountryCode::KW;
	case FPFCountryCode::KG: return PFCountryCode::KG;
	case FPFCountryCode::LA: return PFCountryCode::LA;
	case FPFCountryCode::LV: return PFCountryCode::LV;
	case FPFCountryCode::LB: return PFCountryCode::LB;
	case FPFCountryCode::LS: return PFCountryCode::LS;
	case FPFCountryCode::LR: return PFCountryCode::LR;
	case FPFCountryCode::LY: return PFCountryCode::LY;
	case FPFCountryCode::LI: return PFCountryCode::LI;
	case FPFCountryCode::LT: return PFCountryCode::LT;
	case FPFCountryCode::LU: return PFCountryCode::LU;
	case FPFCountryCode::MO: return PFCountryCode::MO;
	case FPFCountryCode::MK: return PFCountryCode::MK;
	case FPFCountryCode::MG: return PFCountryCode::MG;
	case FPFCountryCode::MW: return PFCountryCode::MW;
	case FPFCountryCode::MY: return PFCountryCode::MY;
	case FPFCountryCode::MV: return PFCountryCode::MV;
	case FPFCountryCode::ML: return PFCountryCode::ML;
	case FPFCountryCode::MT: return PFCountryCode::MT;
	case FPFCountryCode::MH: return PFCountryCode::MH;
	case FPFCountryCode::MQ: return PFCountryCode::MQ;
	case FPFCountryCode::MR: return PFCountryCode::MR;
	case FPFCountryCode::MU: return PFCountryCode::MU;
	case FPFCountryCode::YT: return PFCountryCode::YT;
	case FPFCountryCode::MX: return PFCountryCode::MX;
	case FPFCountryCode::FM: return PFCountryCode::FM;
	case FPFCountryCode::MD: return PFCountryCode::MD;
	case FPFCountryCode::MC: return PFCountryCode::MC;
	case FPFCountryCode::MN: return PFCountryCode::MN;
	case FPFCountryCode::ME: return PFCountryCode::ME;
	case FPFCountryCode::MS: return PFCountryCode::MS;
	case FPFCountryCode::MA: return PFCountryCode::MA;
	case FPFCountryCode::MZ: return PFCountryCode::MZ;
	case FPFCountryCode::MM: return PFCountryCode::MM;
	case FPFCountryCode::NA: return PFCountryCode::NA;
	case FPFCountryCode::NR: return PFCountryCode::NR;
	case FPFCountryCode::NP: return PFCountryCode::NP;
	case FPFCountryCode::NL: return PFCountryCode::NL;
	case FPFCountryCode::NC: return PFCountryCode::NC;
	case FPFCountryCode::NZ: return PFCountryCode::NZ;
	case FPFCountryCode::NI: return PFCountryCode::NI;
	case FPFCountryCode::NE: return PFCountryCode::NE;
	case FPFCountryCode::NG: return PFCountryCode::NG;
	case FPFCountryCode::NU: return PFCountryCode::NU;
	case FPFCountryCode::NF: return PFCountryCode::NF;
	case FPFCountryCode::MP: return PFCountryCode::MP;
	case FPFCountryCode::NO: return PFCountryCode::NO;
	case FPFCountryCode::OM: return PFCountryCode::OM;
	case FPFCountryCode::PK: return PFCountryCode::PK;
	case FPFCountryCode::PW: return PFCountryCode::PW;
	case FPFCountryCode::PS: return PFCountryCode::PS;
	case FPFCountryCode::PA: return PFCountryCode::PA;
	case FPFCountryCode::PG: return PFCountryCode::PG;
	case FPFCountryCode::PY: return PFCountryCode::PY;
	case FPFCountryCode::PE: return PFCountryCode::PE;
	case FPFCountryCode::PH: return PFCountryCode::PH;
	case FPFCountryCode::PN: return PFCountryCode::PN;
	case FPFCountryCode::PL: return PFCountryCode::PL;
	case FPFCountryCode::PT: return PFCountryCode::PT;
	case FPFCountryCode::PR: return PFCountryCode::PR;
	case FPFCountryCode::QA: return PFCountryCode::QA;
	case FPFCountryCode::RE: return PFCountryCode::RE;
	case FPFCountryCode::RO: return PFCountryCode::RO;
	case FPFCountryCode::RU: return PFCountryCode::RU;
	case FPFCountryCode::RW: return PFCountryCode::RW;
	case FPFCountryCode::BL: return PFCountryCode::BL;
	case FPFCountryCode::SH: return PFCountryCode::SH;
	case FPFCountryCode::KN: return PFCountryCode::KN;
	case FPFCountryCode::LC: return PFCountryCode::LC;
	case FPFCountryCode::MF: return PFCountryCode::MF;
	case FPFCountryCode::PM: return PFCountryCode::PM;
	case FPFCountryCode::VC: return PFCountryCode::VC;
	case FPFCountryCode::WS: return PFCountryCode::WS;
	case FPFCountryCode::SM: return PFCountryCode::SM;
	case FPFCountryCode::ST: return PFCountryCode::ST;
	case FPFCountryCode::SA: return PFCountryCode::SA;
	case FPFCountryCode::SN: return PFCountryCode::SN;
	case FPFCountryCode::RS: return PFCountryCode::RS;
	case FPFCountryCode::SC: return PFCountryCode::SC;
	case FPFCountryCode::SL: return PFCountryCode::SL;
	case FPFCountryCode::SG: return PFCountryCode::SG;
	case FPFCountryCode::SX: return PFCountryCode::SX;
	case FPFCountryCode::SK: return PFCountryCode::SK;
	case FPFCountryCode::SI: return PFCountryCode::SI;
	case FPFCountryCode::SB: return PFCountryCode::SB;
	case FPFCountryCode::SO: return PFCountryCode::SO;
	case FPFCountryCode::ZA: return PFCountryCode::ZA;
	case FPFCountryCode::GS: return PFCountryCode::GS;
	case FPFCountryCode::SS: return PFCountryCode::SS;
	case FPFCountryCode::ES: return PFCountryCode::ES;
	case FPFCountryCode::LK: return PFCountryCode::LK;
	case FPFCountryCode::SD: return PFCountryCode::SD;
	case FPFCountryCode::SR: return PFCountryCode::SR;
	case FPFCountryCode::SJ: return PFCountryCode::SJ;
	case FPFCountryCode::SZ: return PFCountryCode::SZ;
	case FPFCountryCode::SE: return PFCountryCode::SE;
	case FPFCountryCode::CH: return PFCountryCode::CH;
	case FPFCountryCode::SY: return PFCountryCode::SY;
	case FPFCountryCode::TW: return PFCountryCode::TW;
	case FPFCountryCode::TJ: return PFCountryCode::TJ;
	case FPFCountryCode::TZ: return PFCountryCode::TZ;
	case FPFCountryCode::TH: return PFCountryCode::TH;
	case FPFCountryCode::TL: return PFCountryCode::TL;
	case FPFCountryCode::TG: return PFCountryCode::TG;
	case FPFCountryCode::TK: return PFCountryCode::TK;
	case FPFCountryCode::TO: return PFCountryCode::TO;
	case FPFCountryCode::TT: return PFCountryCode::TT;
	case FPFCountryCode::TN: return PFCountryCode::TN;
	case FPFCountryCode::TR: return PFCountryCode::TR;
	case FPFCountryCode::TM: return PFCountryCode::TM;
	case FPFCountryCode::TC: return PFCountryCode::TC;
	case FPFCountryCode::TV: return PFCountryCode::TV;
	case FPFCountryCode::UG: return PFCountryCode::UG;
	case FPFCountryCode::UA: return PFCountryCode::UA;
	case FPFCountryCode::AE: return PFCountryCode::AE;
	case FPFCountryCode::GB: return PFCountryCode::GB;
	case FPFCountryCode::US: return PFCountryCode::US;
	case FPFCountryCode::UM: return PFCountryCode::UM;
	case FPFCountryCode::UY: return PFCountryCode::UY;
	case FPFCountryCode::UZ: return PFCountryCode::UZ;
	case FPFCountryCode::VU: return PFCountryCode::VU;
	case FPFCountryCode::VE: return PFCountryCode::VE;
	case FPFCountryCode::VN: return PFCountryCode::VN;
	case FPFCountryCode::VG: return PFCountryCode::VG;
	case FPFCountryCode::VI: return PFCountryCode::VI;
	case FPFCountryCode::WF: return PFCountryCode::WF;
	case FPFCountryCode::EH: return PFCountryCode::EH;
	case FPFCountryCode::YE: return PFCountryCode::YE;
	case FPFCountryCode::ZM: return PFCountryCode::ZM;
	case FPFCountryCode::ZW: return PFCountryCode::ZW;
	case FPFCountryCode::Unknown: return PFCountryCode::Unknown;
	default:
	return PFCountryCode::AF;
	}
}

const FPFSubscriptionProviderStatus ConvertSubscriptionProviderStatusToUnreal(const PFSubscriptionProviderStatus* enumVal)
{
	if (enumVal == nullptr) {
		return FPFSubscriptionProviderStatus::NoError;
	}

	switch(*enumVal)
	{
	case PFSubscriptionProviderStatus::NoError: return FPFSubscriptionProviderStatus::NoError;
	case PFSubscriptionProviderStatus::Cancelled: return FPFSubscriptionProviderStatus::Cancelled;
	case PFSubscriptionProviderStatus::UnknownError: return FPFSubscriptionProviderStatus::UnknownError;
	case PFSubscriptionProviderStatus::BillingError: return FPFSubscriptionProviderStatus::BillingError;
	case PFSubscriptionProviderStatus::ProductUnavailable: return FPFSubscriptionProviderStatus::ProductUnavailable;
	case PFSubscriptionProviderStatus::CustomerDidNotAcceptPriceChange: return FPFSubscriptionProviderStatus::CustomerDidNotAcceptPriceChange;
	case PFSubscriptionProviderStatus::FreeTrial: return FPFSubscriptionProviderStatus::FreeTrial;
	case PFSubscriptionProviderStatus::PaymentPending: return FPFSubscriptionProviderStatus::PaymentPending;
	default:
	return FPFSubscriptionProviderStatus::NoError;
	}
}

const PFSubscriptionProviderStatus ConvertSubscriptionProviderStatusToPlayfab(TSharedPtr<const FPFSubscriptionProviderStatus> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFSubscriptionProviderStatus::NoError;
	}

	switch(*enumVal)
	{
	case FPFSubscriptionProviderStatus::NoError: return PFSubscriptionProviderStatus::NoError;
	case FPFSubscriptionProviderStatus::Cancelled: return PFSubscriptionProviderStatus::Cancelled;
	case FPFSubscriptionProviderStatus::UnknownError: return PFSubscriptionProviderStatus::UnknownError;
	case FPFSubscriptionProviderStatus::BillingError: return PFSubscriptionProviderStatus::BillingError;
	case FPFSubscriptionProviderStatus::ProductUnavailable: return PFSubscriptionProviderStatus::ProductUnavailable;
	case FPFSubscriptionProviderStatus::CustomerDidNotAcceptPriceChange: return PFSubscriptionProviderStatus::CustomerDidNotAcceptPriceChange;
	case FPFSubscriptionProviderStatus::FreeTrial: return PFSubscriptionProviderStatus::FreeTrial;
	case FPFSubscriptionProviderStatus::PaymentPending: return PFSubscriptionProviderStatus::PaymentPending;
	default:
	return PFSubscriptionProviderStatus::NoError;
	}
}

const FPFPushNotificationPlatform ConvertPushNotificationPlatformToUnreal(const PFPushNotificationPlatform* enumVal)
{
	if (enumVal == nullptr) {
		return FPFPushNotificationPlatform::ApplePushNotificationService;
	}

	switch(*enumVal)
	{
	case PFPushNotificationPlatform::ApplePushNotificationService: return FPFPushNotificationPlatform::ApplePushNotificationService;
	case PFPushNotificationPlatform::GoogleCloudMessaging: return FPFPushNotificationPlatform::GoogleCloudMessaging;
	default:
	return FPFPushNotificationPlatform::ApplePushNotificationService;
	}
}

const PFPushNotificationPlatform ConvertPushNotificationPlatformToPlayfab(TSharedPtr<const FPFPushNotificationPlatform> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFPushNotificationPlatform::ApplePushNotificationService;
	}

	switch(*enumVal)
	{
	case FPFPushNotificationPlatform::ApplePushNotificationService: return PFPushNotificationPlatform::ApplePushNotificationService;
	case FPFPushNotificationPlatform::GoogleCloudMessaging: return PFPushNotificationPlatform::GoogleCloudMessaging;
	default:
	return PFPushNotificationPlatform::ApplePushNotificationService;
	}
}

TSharedPtr<const FPFItemInstance> ConvertItemInstanceToUnreal(const PFItemInstance* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFItemInstance> ConvertedType = MakeShared<FPFItemInstance>(FPFItemInstance{
		.annotation = Datatype->annotation == nullptr ? FString() : FString(Datatype->annotation),
		.bundleContents = ConvertCharArrayToUnreal(Datatype->bundleContents, Datatype->bundleContentsCount),
		.bundleContentsCount = Datatype->bundleContentsCount,
		.bundleParent = Datatype->bundleParent == nullptr ? FString() : FString(Datatype->bundleParent),
		.catalogVersion = Datatype->catalogVersion == nullptr ? FString() : FString(Datatype->catalogVersion),
		.customData = ConvertCharMapToUnreal(Datatype->customData, Datatype->customDataCount),
		.customDataCount = Datatype->customDataCount,
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.expiration = ConvertTimeToUnreal(Datatype->expiration),
		.itemClass = Datatype->itemClass == nullptr ? FString() : FString(Datatype->itemClass),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.itemInstanceId = Datatype->itemInstanceId == nullptr ? FString() : FString(Datatype->itemInstanceId),
		.purchaseDate = ConvertTimeToUnreal(Datatype->purchaseDate),
		.remainingUses = TSharedPtr<const int32>(Datatype->remainingUses),
		.unitCurrency = Datatype->unitCurrency == nullptr ? FString() : FString(Datatype->unitCurrency),
		.unitPrice = Datatype->unitPrice,
		.usesIncrementedBy = TSharedPtr<const int32>(Datatype->usesIncrementedBy)
	});

	return ConvertedType;
}

const PFItemInstance* ConvertItemInstanceToPlayfab(TSharedPtr<const FPFItemInstance> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFItemInstance* ConvertedType = new PFItemInstance{
		.annotation = ConvertFStringToCharPtr(Datatype->annotation),
		.bundleContents = ConvertFStringArrayToPlayfab(Datatype->bundleContents),
		.bundleContentsCount = (uint32_t)Datatype->bundleContents.Num(),
		.bundleParent = ConvertFStringToCharPtr(Datatype->bundleParent),
		.catalogVersion = ConvertFStringToCharPtr(Datatype->catalogVersion),
		.customData = ConvertFStringMapToPlayfab(Datatype->customData),
		.customDataCount = (uint32_t)Datatype->customData.Num(),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.expiration = ConvertFDateTimeToPlayfab(Datatype->expiration),
		.itemClass = ConvertFStringToCharPtr(Datatype->itemClass),
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.itemInstanceId = ConvertFStringToCharPtr(Datatype->itemInstanceId),
		.purchaseDate = ConvertFDateTimeToPlayfab(Datatype->purchaseDate),
		.remainingUses = new int32(*Datatype->remainingUses),
		.unitCurrency = ConvertFStringToCharPtr(Datatype->unitCurrency),
		.unitPrice = Datatype->unitPrice,
		.usesIncrementedBy = new int32(*Datatype->usesIncrementedBy)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserAndroidDeviceInfo> ConvertUserAndroidDeviceInfoToUnreal(const PFUserAndroidDeviceInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserAndroidDeviceInfo> ConvertedType = MakeShared<FPFUserAndroidDeviceInfo>(FPFUserAndroidDeviceInfo{
		.androidDeviceId = Datatype->androidDeviceId == nullptr ? FString() : FString(Datatype->androidDeviceId)
	});

	return ConvertedType;
}

const PFUserAndroidDeviceInfo* ConvertUserAndroidDeviceInfoToPlayfab(TSharedPtr<const FPFUserAndroidDeviceInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserAndroidDeviceInfo* ConvertedType = new PFUserAndroidDeviceInfo{
		.androidDeviceId = ConvertFStringToCharPtr(Datatype->androidDeviceId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserAppleIdInfo> ConvertUserAppleIdInfoToUnreal(const PFUserAppleIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserAppleIdInfo> ConvertedType = MakeShared<FPFUserAppleIdInfo>(FPFUserAppleIdInfo{
		.appleSubjectId = Datatype->appleSubjectId == nullptr ? FString() : FString(Datatype->appleSubjectId)
	});

	return ConvertedType;
}

const PFUserAppleIdInfo* ConvertUserAppleIdInfoToPlayfab(TSharedPtr<const FPFUserAppleIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserAppleIdInfo* ConvertedType = new PFUserAppleIdInfo{
		.appleSubjectId = ConvertFStringToCharPtr(Datatype->appleSubjectId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserBattleNetInfo> ConvertUserBattleNetInfoToUnreal(const PFUserBattleNetInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserBattleNetInfo> ConvertedType = MakeShared<FPFUserBattleNetInfo>(FPFUserBattleNetInfo{
		.battleNetAccountId = Datatype->battleNetAccountId == nullptr ? FString() : FString(Datatype->battleNetAccountId),
		.battleNetBattleTag = Datatype->battleNetBattleTag == nullptr ? FString() : FString(Datatype->battleNetBattleTag)
	});

	return ConvertedType;
}

const PFUserBattleNetInfo* ConvertUserBattleNetInfoToPlayfab(TSharedPtr<const FPFUserBattleNetInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserBattleNetInfo* ConvertedType = new PFUserBattleNetInfo{
		.battleNetAccountId = ConvertFStringToCharPtr(Datatype->battleNetAccountId),
		.battleNetBattleTag = ConvertFStringToCharPtr(Datatype->battleNetBattleTag)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserCustomIdInfo> ConvertUserCustomIdInfoToUnreal(const PFUserCustomIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserCustomIdInfo> ConvertedType = MakeShared<FPFUserCustomIdInfo>(FPFUserCustomIdInfo{
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId)
	});

	return ConvertedType;
}

const PFUserCustomIdInfo* ConvertUserCustomIdInfoToPlayfab(TSharedPtr<const FPFUserCustomIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserCustomIdInfo* ConvertedType = new PFUserCustomIdInfo{
		.customId = ConvertFStringToCharPtr(Datatype->customId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserFacebookInfo> ConvertUserFacebookInfoToUnreal(const PFUserFacebookInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserFacebookInfo> ConvertedType = MakeShared<FPFUserFacebookInfo>(FPFUserFacebookInfo{
		.facebookId = Datatype->facebookId == nullptr ? FString() : FString(Datatype->facebookId),
		.fullName = Datatype->fullName == nullptr ? FString() : FString(Datatype->fullName)
	});

	return ConvertedType;
}

const PFUserFacebookInfo* ConvertUserFacebookInfoToPlayfab(TSharedPtr<const FPFUserFacebookInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserFacebookInfo* ConvertedType = new PFUserFacebookInfo{
		.facebookId = ConvertFStringToCharPtr(Datatype->facebookId),
		.fullName = ConvertFStringToCharPtr(Datatype->fullName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserFacebookInstantGamesIdInfo> ConvertUserFacebookInstantGamesIdInfoToUnreal(const PFUserFacebookInstantGamesIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserFacebookInstantGamesIdInfo> ConvertedType = MakeShared<FPFUserFacebookInstantGamesIdInfo>(FPFUserFacebookInstantGamesIdInfo{
		.facebookInstantGamesId = Datatype->facebookInstantGamesId == nullptr ? FString() : FString(Datatype->facebookInstantGamesId)
	});

	return ConvertedType;
}

const PFUserFacebookInstantGamesIdInfo* ConvertUserFacebookInstantGamesIdInfoToPlayfab(TSharedPtr<const FPFUserFacebookInstantGamesIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserFacebookInstantGamesIdInfo* ConvertedType = new PFUserFacebookInstantGamesIdInfo{
		.facebookInstantGamesId = ConvertFStringToCharPtr(Datatype->facebookInstantGamesId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserGameCenterInfo> ConvertUserGameCenterInfoToUnreal(const PFUserGameCenterInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserGameCenterInfo> ConvertedType = MakeShared<FPFUserGameCenterInfo>(FPFUserGameCenterInfo{
		.gameCenterId = Datatype->gameCenterId == nullptr ? FString() : FString(Datatype->gameCenterId)
	});

	return ConvertedType;
}

const PFUserGameCenterInfo* ConvertUserGameCenterInfoToPlayfab(TSharedPtr<const FPFUserGameCenterInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserGameCenterInfo* ConvertedType = new PFUserGameCenterInfo{
		.gameCenterId = ConvertFStringToCharPtr(Datatype->gameCenterId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserGoogleInfo> ConvertUserGoogleInfoToUnreal(const PFUserGoogleInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserGoogleInfo> ConvertedType = MakeShared<FPFUserGoogleInfo>(FPFUserGoogleInfo{
		.googleEmail = Datatype->googleEmail == nullptr ? FString() : FString(Datatype->googleEmail),
		.googleGender = Datatype->googleGender == nullptr ? FString() : FString(Datatype->googleGender),
		.googleId = Datatype->googleId == nullptr ? FString() : FString(Datatype->googleId),
		.googleLocale = Datatype->googleLocale == nullptr ? FString() : FString(Datatype->googleLocale),
		.googleName = Datatype->googleName == nullptr ? FString() : FString(Datatype->googleName)
	});

	return ConvertedType;
}

const PFUserGoogleInfo* ConvertUserGoogleInfoToPlayfab(TSharedPtr<const FPFUserGoogleInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserGoogleInfo* ConvertedType = new PFUserGoogleInfo{
		.googleEmail = ConvertFStringToCharPtr(Datatype->googleEmail),
		.googleGender = ConvertFStringToCharPtr(Datatype->googleGender),
		.googleId = ConvertFStringToCharPtr(Datatype->googleId),
		.googleLocale = ConvertFStringToCharPtr(Datatype->googleLocale),
		.googleName = ConvertFStringToCharPtr(Datatype->googleName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserGooglePlayGamesInfo> ConvertUserGooglePlayGamesInfoToUnreal(const PFUserGooglePlayGamesInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserGooglePlayGamesInfo> ConvertedType = MakeShared<FPFUserGooglePlayGamesInfo>(FPFUserGooglePlayGamesInfo{
		.googlePlayGamesPlayerAvatarImageUrl = Datatype->googlePlayGamesPlayerAvatarImageUrl == nullptr ? FString() : FString(Datatype->googlePlayGamesPlayerAvatarImageUrl),
		.googlePlayGamesPlayerDisplayName = Datatype->googlePlayGamesPlayerDisplayName == nullptr ? FString() : FString(Datatype->googlePlayGamesPlayerDisplayName),
		.googlePlayGamesPlayerId = Datatype->googlePlayGamesPlayerId == nullptr ? FString() : FString(Datatype->googlePlayGamesPlayerId)
	});

	return ConvertedType;
}

const PFUserGooglePlayGamesInfo* ConvertUserGooglePlayGamesInfoToPlayfab(TSharedPtr<const FPFUserGooglePlayGamesInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserGooglePlayGamesInfo* ConvertedType = new PFUserGooglePlayGamesInfo{
		.googlePlayGamesPlayerAvatarImageUrl = ConvertFStringToCharPtr(Datatype->googlePlayGamesPlayerAvatarImageUrl),
		.googlePlayGamesPlayerDisplayName = ConvertFStringToCharPtr(Datatype->googlePlayGamesPlayerDisplayName),
		.googlePlayGamesPlayerId = ConvertFStringToCharPtr(Datatype->googlePlayGamesPlayerId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserIosDeviceInfo> ConvertUserIosDeviceInfoToUnreal(const PFUserIosDeviceInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserIosDeviceInfo> ConvertedType = MakeShared<FPFUserIosDeviceInfo>(FPFUserIosDeviceInfo{
		.iosDeviceId = Datatype->iosDeviceId == nullptr ? FString() : FString(Datatype->iosDeviceId)
	});

	return ConvertedType;
}

const PFUserIosDeviceInfo* ConvertUserIosDeviceInfoToPlayfab(TSharedPtr<const FPFUserIosDeviceInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserIosDeviceInfo* ConvertedType = new PFUserIosDeviceInfo{
		.iosDeviceId = ConvertFStringToCharPtr(Datatype->iosDeviceId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserKongregateInfo> ConvertUserKongregateInfoToUnreal(const PFUserKongregateInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserKongregateInfo> ConvertedType = MakeShared<FPFUserKongregateInfo>(FPFUserKongregateInfo{
		.kongregateId = Datatype->kongregateId == nullptr ? FString() : FString(Datatype->kongregateId),
		.kongregateName = Datatype->kongregateName == nullptr ? FString() : FString(Datatype->kongregateName)
	});

	return ConvertedType;
}

const PFUserKongregateInfo* ConvertUserKongregateInfoToPlayfab(TSharedPtr<const FPFUserKongregateInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserKongregateInfo* ConvertedType = new PFUserKongregateInfo{
		.kongregateId = ConvertFStringToCharPtr(Datatype->kongregateId),
		.kongregateName = ConvertFStringToCharPtr(Datatype->kongregateName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserNintendoSwitchAccountIdInfo> ConvertUserNintendoSwitchAccountIdInfoToUnreal(const PFUserNintendoSwitchAccountIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserNintendoSwitchAccountIdInfo> ConvertedType = MakeShared<FPFUserNintendoSwitchAccountIdInfo>(FPFUserNintendoSwitchAccountIdInfo{
		.nintendoSwitchAccountSubjectId = Datatype->nintendoSwitchAccountSubjectId == nullptr ? FString() : FString(Datatype->nintendoSwitchAccountSubjectId)
	});

	return ConvertedType;
}

const PFUserNintendoSwitchAccountIdInfo* ConvertUserNintendoSwitchAccountIdInfoToPlayfab(TSharedPtr<const FPFUserNintendoSwitchAccountIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserNintendoSwitchAccountIdInfo* ConvertedType = new PFUserNintendoSwitchAccountIdInfo{
		.nintendoSwitchAccountSubjectId = ConvertFStringToCharPtr(Datatype->nintendoSwitchAccountSubjectId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserNintendoSwitchDeviceIdInfo> ConvertUserNintendoSwitchDeviceIdInfoToUnreal(const PFUserNintendoSwitchDeviceIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserNintendoSwitchDeviceIdInfo> ConvertedType = MakeShared<FPFUserNintendoSwitchDeviceIdInfo>(FPFUserNintendoSwitchDeviceIdInfo{
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId)
	});

	return ConvertedType;
}

const PFUserNintendoSwitchDeviceIdInfo* ConvertUserNintendoSwitchDeviceIdInfoToPlayfab(TSharedPtr<const FPFUserNintendoSwitchDeviceIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserNintendoSwitchDeviceIdInfo* ConvertedType = new PFUserNintendoSwitchDeviceIdInfo{
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserOpenIdInfo> ConvertUserOpenIdInfoToUnreal(const PFUserOpenIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserOpenIdInfo> ConvertedType = MakeShared<FPFUserOpenIdInfo>(FPFUserOpenIdInfo{
		.connectionId = Datatype->connectionId == nullptr ? FString() : FString(Datatype->connectionId),
		.issuer = Datatype->issuer == nullptr ? FString() : FString(Datatype->issuer),
		.subject = Datatype->subject == nullptr ? FString() : FString(Datatype->subject)
	});

	return ConvertedType;
}

const PFUserOpenIdInfo* ConvertUserOpenIdInfoToPlayfab(TSharedPtr<const FPFUserOpenIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserOpenIdInfo* ConvertedType = new PFUserOpenIdInfo{
		.connectionId = ConvertFStringToCharPtr(Datatype->connectionId),
		.issuer = ConvertFStringToCharPtr(Datatype->issuer),
		.subject = ConvertFStringToCharPtr(Datatype->subject)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserPrivateAccountInfo> ConvertUserPrivateAccountInfoToUnreal(const PFUserPrivateAccountInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserPrivateAccountInfo> ConvertedType = MakeShared<FPFUserPrivateAccountInfo>(FPFUserPrivateAccountInfo{
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email)
	});

	return ConvertedType;
}

const PFUserPrivateAccountInfo* ConvertUserPrivateAccountInfoToPlayfab(TSharedPtr<const FPFUserPrivateAccountInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserPrivateAccountInfo* ConvertedType = new PFUserPrivateAccountInfo{
		.email = ConvertFStringToCharPtr(Datatype->email)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserPsnInfo> ConvertUserPsnInfoToUnreal(const PFUserPsnInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserPsnInfo> ConvertedType = MakeShared<FPFUserPsnInfo>(FPFUserPsnInfo{
		.psnAccountId = Datatype->psnAccountId == nullptr ? FString() : FString(Datatype->psnAccountId),
		.psnOnlineId = Datatype->psnOnlineId == nullptr ? FString() : FString(Datatype->psnOnlineId)
	});

	return ConvertedType;
}

const PFUserPsnInfo* ConvertUserPsnInfoToPlayfab(TSharedPtr<const FPFUserPsnInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserPsnInfo* ConvertedType = new PFUserPsnInfo{
		.psnAccountId = ConvertFStringToCharPtr(Datatype->psnAccountId),
		.psnOnlineId = ConvertFStringToCharPtr(Datatype->psnOnlineId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserServerCustomIdInfo> ConvertUserServerCustomIdInfoToUnreal(const PFUserServerCustomIdInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserServerCustomIdInfo> ConvertedType = MakeShared<FPFUserServerCustomIdInfo>(FPFUserServerCustomIdInfo{
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId)
	});

	return ConvertedType;
}

const PFUserServerCustomIdInfo* ConvertUserServerCustomIdInfoToPlayfab(TSharedPtr<const FPFUserServerCustomIdInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserServerCustomIdInfo* ConvertedType = new PFUserServerCustomIdInfo{
		.customId = ConvertFStringToCharPtr(Datatype->customId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserSteamInfo> ConvertUserSteamInfoToUnreal(const PFUserSteamInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserSteamInfo> ConvertedType = MakeShared<FPFUserSteamInfo>(FPFUserSteamInfo{
		.steamActivationStatus = MakeShared<FPFTitleActivationStatus>(ConvertTitleActivationStatusToUnreal(Datatype->steamActivationStatus)),
		.steamCountry = Datatype->steamCountry == nullptr ? FString() : FString(Datatype->steamCountry),
		.steamCurrency = MakeShared<FPFCurrency>(ConvertCurrencyToUnreal(Datatype->steamCurrency)),
		.steamId = Datatype->steamId == nullptr ? FString() : FString(Datatype->steamId),
		.steamName = Datatype->steamName == nullptr ? FString() : FString(Datatype->steamName)
	});

	return ConvertedType;
}

const PFUserSteamInfo* ConvertUserSteamInfoToPlayfab(TSharedPtr<const FPFUserSteamInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserSteamInfo* ConvertedType = new PFUserSteamInfo{
		.steamActivationStatus = new PFTitleActivationStatus(ConvertTitleActivationStatusToPlayfab(Datatype->steamActivationStatus)),
		.steamCountry = ConvertFStringToCharPtr(Datatype->steamCountry),
		.steamCurrency = new PFCurrency(ConvertCurrencyToPlayfab(Datatype->steamCurrency)),
		.steamId = ConvertFStringToCharPtr(Datatype->steamId),
		.steamName = ConvertFStringToCharPtr(Datatype->steamName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserTitleInfo> ConvertUserTitleInfoToUnreal(const PFUserTitleInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserTitleInfo> ConvertedType = MakeShared<FPFUserTitleInfo>(FPFUserTitleInfo{
		.avatarUrl = Datatype->avatarUrl == nullptr ? FString() : FString(Datatype->avatarUrl),
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.firstLogin = ConvertTimeToUnreal(Datatype->firstLogin),
		.isBanned = TSharedPtr<const bool>(Datatype->isBanned),
		.lastLogin = ConvertTimeToUnreal(Datatype->lastLogin),
		.origination = MakeShared<FPFUserOrigination>(ConvertUserOriginationToUnreal(Datatype->origination)),
		.titlePlayerAccount = ConvertEntityKeyToUnreal(Datatype->titlePlayerAccount)
	});

	return ConvertedType;
}

const PFUserTitleInfo* ConvertUserTitleInfoToPlayfab(TSharedPtr<const FPFUserTitleInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserTitleInfo* ConvertedType = new PFUserTitleInfo{
		.avatarUrl = ConvertFStringToCharPtr(Datatype->avatarUrl),
		.created = Datatype->created.ToUnixTimestamp(),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.firstLogin = ConvertFDateTimeToPlayfab(Datatype->firstLogin),
		.isBanned = new bool(*Datatype->isBanned),
		.lastLogin = ConvertFDateTimeToPlayfab(Datatype->lastLogin),
		.origination = new PFUserOrigination(ConvertUserOriginationToPlayfab(Datatype->origination)),
		.titlePlayerAccount = ConvertEntityKeyToPlayfab(Datatype->titlePlayerAccount)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserTwitchInfo> ConvertUserTwitchInfoToUnreal(const PFUserTwitchInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserTwitchInfo> ConvertedType = MakeShared<FPFUserTwitchInfo>(FPFUserTwitchInfo{
		.twitchId = Datatype->twitchId == nullptr ? FString() : FString(Datatype->twitchId),
		.twitchUserName = Datatype->twitchUserName == nullptr ? FString() : FString(Datatype->twitchUserName)
	});

	return ConvertedType;
}

const PFUserTwitchInfo* ConvertUserTwitchInfoToPlayfab(TSharedPtr<const FPFUserTwitchInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserTwitchInfo* ConvertedType = new PFUserTwitchInfo{
		.twitchId = ConvertFStringToCharPtr(Datatype->twitchId),
		.twitchUserName = ConvertFStringToCharPtr(Datatype->twitchUserName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserXboxInfo> ConvertUserXboxInfoToUnreal(const PFUserXboxInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserXboxInfo> ConvertedType = MakeShared<FPFUserXboxInfo>(FPFUserXboxInfo{
		.xboxUserId = Datatype->xboxUserId == nullptr ? FString() : FString(Datatype->xboxUserId),
		.xboxUserSandbox = Datatype->xboxUserSandbox == nullptr ? FString() : FString(Datatype->xboxUserSandbox)
	});

	return ConvertedType;
}

const PFUserXboxInfo* ConvertUserXboxInfoToPlayfab(TSharedPtr<const FPFUserXboxInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserXboxInfo* ConvertedType = new PFUserXboxInfo{
		.xboxUserId = ConvertFStringToCharPtr(Datatype->xboxUserId),
		.xboxUserSandbox = ConvertFStringToCharPtr(Datatype->xboxUserSandbox)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserAccountInfo> ConvertUserAccountInfoToUnreal(const PFUserAccountInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserAccountInfo> ConvertedType = MakeShared<FPFUserAccountInfo>(FPFUserAccountInfo{
		.androidDeviceInfo = ConvertUserAndroidDeviceInfoToUnreal(Datatype->androidDeviceInfo),
		.appleAccountInfo = ConvertUserAppleIdInfoToUnreal(Datatype->appleAccountInfo),
		.battleNetAccountInfo = ConvertUserBattleNetInfoToUnreal(Datatype->battleNetAccountInfo),
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.customIdInfo = ConvertUserCustomIdInfoToUnreal(Datatype->customIdInfo),
		.facebookInfo = ConvertUserFacebookInfoToUnreal(Datatype->facebookInfo),
		.facebookInstantGamesIdInfo = ConvertUserFacebookInstantGamesIdInfoToUnreal(Datatype->facebookInstantGamesIdInfo),
		.gameCenterInfo = ConvertUserGameCenterInfoToUnreal(Datatype->gameCenterInfo),
		.googleInfo = ConvertUserGoogleInfoToUnreal(Datatype->googleInfo),
		.googlePlayGamesInfo = ConvertUserGooglePlayGamesInfoToUnreal(Datatype->googlePlayGamesInfo),
		.iosDeviceInfo = ConvertUserIosDeviceInfoToUnreal(Datatype->iosDeviceInfo),
		.kongregateInfo = ConvertUserKongregateInfoToUnreal(Datatype->kongregateInfo),
		.nintendoSwitchAccountInfo = ConvertUserNintendoSwitchAccountIdInfoToUnreal(Datatype->nintendoSwitchAccountInfo),
		.nintendoSwitchDeviceIdInfo = ConvertUserNintendoSwitchDeviceIdInfoToUnreal(Datatype->nintendoSwitchDeviceIdInfo),
		.openIdInfo = ConvertPlayfabArrayToUnreal(Datatype->openIdInfo, Datatype->openIdInfoCount, ConvertUserOpenIdInfoToUnreal),
		.openIdInfoCount = Datatype->openIdInfoCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.privateInfo = ConvertUserPrivateAccountInfoToUnreal(Datatype->privateInfo),
		.psnInfo = ConvertUserPsnInfoToUnreal(Datatype->psnInfo),
		.serverCustomIdInfo = ConvertUserServerCustomIdInfoToUnreal(Datatype->serverCustomIdInfo),
		.steamInfo = ConvertUserSteamInfoToUnreal(Datatype->steamInfo),
		.titleInfo = ConvertUserTitleInfoToUnreal(Datatype->titleInfo),
		.twitchInfo = ConvertUserTwitchInfoToUnreal(Datatype->twitchInfo),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username),
		.xboxInfo = ConvertUserXboxInfoToUnreal(Datatype->xboxInfo)
	});

	return ConvertedType;
}

const PFUserAccountInfo* ConvertUserAccountInfoToPlayfab(TSharedPtr<const FPFUserAccountInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserAccountInfo* ConvertedType = new PFUserAccountInfo{
		.androidDeviceInfo = ConvertUserAndroidDeviceInfoToPlayfab(Datatype->androidDeviceInfo),
		.appleAccountInfo = ConvertUserAppleIdInfoToPlayfab(Datatype->appleAccountInfo),
		.battleNetAccountInfo = ConvertUserBattleNetInfoToPlayfab(Datatype->battleNetAccountInfo),
		.created = Datatype->created.ToUnixTimestamp(),
		.customIdInfo = ConvertUserCustomIdInfoToPlayfab(Datatype->customIdInfo),
		.facebookInfo = ConvertUserFacebookInfoToPlayfab(Datatype->facebookInfo),
		.facebookInstantGamesIdInfo = ConvertUserFacebookInstantGamesIdInfoToPlayfab(Datatype->facebookInstantGamesIdInfo),
		.gameCenterInfo = ConvertUserGameCenterInfoToPlayfab(Datatype->gameCenterInfo),
		.googleInfo = ConvertUserGoogleInfoToPlayfab(Datatype->googleInfo),
		.googlePlayGamesInfo = ConvertUserGooglePlayGamesInfoToPlayfab(Datatype->googlePlayGamesInfo),
		.iosDeviceInfo = ConvertUserIosDeviceInfoToPlayfab(Datatype->iosDeviceInfo),
		.kongregateInfo = ConvertUserKongregateInfoToPlayfab(Datatype->kongregateInfo),
		.nintendoSwitchAccountInfo = ConvertUserNintendoSwitchAccountIdInfoToPlayfab(Datatype->nintendoSwitchAccountInfo),
		.nintendoSwitchDeviceIdInfo = ConvertUserNintendoSwitchDeviceIdInfoToPlayfab(Datatype->nintendoSwitchDeviceIdInfo),
		.openIdInfo = ConvertUnrealArrayToPlayfab(Datatype->openIdInfo, ConvertUserOpenIdInfoToPlayfab),
		.openIdInfoCount = (uint32_t)Datatype->openIdInfo.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.privateInfo = ConvertUserPrivateAccountInfoToPlayfab(Datatype->privateInfo),
		.psnInfo = ConvertUserPsnInfoToPlayfab(Datatype->psnInfo),
		.serverCustomIdInfo = ConvertUserServerCustomIdInfoToPlayfab(Datatype->serverCustomIdInfo),
		.steamInfo = ConvertUserSteamInfoToPlayfab(Datatype->steamInfo),
		.titleInfo = ConvertUserTitleInfoToPlayfab(Datatype->titleInfo),
		.twitchInfo = ConvertUserTwitchInfoToPlayfab(Datatype->twitchInfo),
		.username = ConvertFStringToCharPtr(Datatype->username),
		.xboxInfo = ConvertUserXboxInfoToPlayfab(Datatype->xboxInfo)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCharacterResult> ConvertCharacterResultToUnreal(const PFCharacterResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCharacterResult> ConvertedType = MakeShared<FPFCharacterResult>(FPFCharacterResult{
		.characterId = Datatype->characterId == nullptr ? FString() : FString(Datatype->characterId),
		.characterName = Datatype->characterName == nullptr ? FString() : FString(Datatype->characterName),
		.characterType = Datatype->characterType == nullptr ? FString() : FString(Datatype->characterType)
	});

	return ConvertedType;
}

const PFCharacterResult* ConvertCharacterResultToPlayfab(TSharedPtr<const FPFCharacterResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCharacterResult* ConvertedType = new PFCharacterResult{
		.characterId = ConvertFStringToCharPtr(Datatype->characterId),
		.characterName = ConvertFStringToCharPtr(Datatype->characterName),
		.characterType = ConvertFStringToCharPtr(Datatype->characterType)
	};

	return ConvertedType;
}

TSharedPtr<const FPFUserDataRecord> ConvertUserDataRecordToUnreal(const PFUserDataRecord* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFUserDataRecord> ConvertedType = MakeShared<FPFUserDataRecord>(FPFUserDataRecord{
		.lastUpdated = FDateTime::FromUnixTimestamp((int64)Datatype->lastUpdated),
		.permission = MakeShared<FPFUserDataPermission>(ConvertUserDataPermissionToUnreal(Datatype->permission)),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFUserDataRecord* ConvertUserDataRecordToPlayfab(TSharedPtr<const FPFUserDataRecord> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFUserDataRecord* ConvertedType = new PFUserDataRecord{
		.lastUpdated = Datatype->lastUpdated.ToUnixTimestamp(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Datatype->permission)),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}

TSharedPtr<const FPFVirtualCurrencyRechargeTime> ConvertVirtualCurrencyRechargeTimeToUnreal(const PFVirtualCurrencyRechargeTime* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFVirtualCurrencyRechargeTime> ConvertedType = MakeShared<FPFVirtualCurrencyRechargeTime>(FPFVirtualCurrencyRechargeTime{
		.rechargeMax = Datatype->rechargeMax,
		.rechargeTime = FDateTime::FromUnixTimestamp((int64)Datatype->rechargeTime),
		.secondsToRecharge = Datatype->secondsToRecharge
	});

	return ConvertedType;
}

const PFVirtualCurrencyRechargeTime* ConvertVirtualCurrencyRechargeTimeToPlayfab(TSharedPtr<const FPFVirtualCurrencyRechargeTime> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFVirtualCurrencyRechargeTime* ConvertedType = new PFVirtualCurrencyRechargeTime{
		.rechargeMax = Datatype->rechargeMax,
		.rechargeTime = Datatype->rechargeTime.ToUnixTimestamp(),
		.secondsToRecharge = Datatype->secondsToRecharge
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerProfileViewConstraints> ConvertPlayerProfileViewConstraintsToUnreal(const PFPlayerProfileViewConstraints* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerProfileViewConstraints> ConvertedType = MakeShared<FPFPlayerProfileViewConstraints>(FPFPlayerProfileViewConstraints{
		.showAvatarUrl = Datatype->showAvatarUrl,
		.showBannedUntil = Datatype->showBannedUntil,
		.showCampaignAttributions = Datatype->showCampaignAttributions,
		.showContactEmailAddresses = Datatype->showContactEmailAddresses,
		.showCreated = Datatype->showCreated,
		.showDisplayName = Datatype->showDisplayName,
		.showExperimentVariants = Datatype->showExperimentVariants,
		.showLastLogin = Datatype->showLastLogin,
		.showLinkedAccounts = Datatype->showLinkedAccounts,
		.showLocations = Datatype->showLocations,
		.showMemberships = Datatype->showMemberships,
		.showOrigination = Datatype->showOrigination,
		.showPushNotificationRegistrations = Datatype->showPushNotificationRegistrations,
		.showStatistics = Datatype->showStatistics,
		.showTags = Datatype->showTags,
		.showTotalValueToDateInUsd = Datatype->showTotalValueToDateInUsd,
		.showValuesToDate = Datatype->showValuesToDate
	});

	return ConvertedType;
}

const PFPlayerProfileViewConstraints* ConvertPlayerProfileViewConstraintsToPlayfab(TSharedPtr<const FPFPlayerProfileViewConstraints> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerProfileViewConstraints* ConvertedType = new PFPlayerProfileViewConstraints{
		.showAvatarUrl = Datatype->showAvatarUrl,
		.showBannedUntil = Datatype->showBannedUntil,
		.showCampaignAttributions = Datatype->showCampaignAttributions,
		.showContactEmailAddresses = Datatype->showContactEmailAddresses,
		.showCreated = Datatype->showCreated,
		.showDisplayName = Datatype->showDisplayName,
		.showExperimentVariants = Datatype->showExperimentVariants,
		.showLastLogin = Datatype->showLastLogin,
		.showLinkedAccounts = Datatype->showLinkedAccounts,
		.showLocations = Datatype->showLocations,
		.showMemberships = Datatype->showMemberships,
		.showOrigination = Datatype->showOrigination,
		.showPushNotificationRegistrations = Datatype->showPushNotificationRegistrations,
		.showStatistics = Datatype->showStatistics,
		.showTags = Datatype->showTags,
		.showTotalValueToDateInUsd = Datatype->showTotalValueToDateInUsd,
		.showValuesToDate = Datatype->showValuesToDate
	};

	return ConvertedType;
}

TSharedPtr<const FPFAdCampaignAttributionModel> ConvertAdCampaignAttributionModelToUnreal(const PFAdCampaignAttributionModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAdCampaignAttributionModel> ConvertedType = MakeShared<FPFAdCampaignAttributionModel>(FPFAdCampaignAttributionModel{
		.attributedAt = FDateTime::FromUnixTimestamp((int64)Datatype->attributedAt),
		.campaignId = Datatype->campaignId == nullptr ? FString() : FString(Datatype->campaignId),
		.platform = Datatype->platform == nullptr ? FString() : FString(Datatype->platform)
	});

	return ConvertedType;
}

const PFAdCampaignAttributionModel* ConvertAdCampaignAttributionModelToPlayfab(TSharedPtr<const FPFAdCampaignAttributionModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAdCampaignAttributionModel* ConvertedType = new PFAdCampaignAttributionModel{
		.attributedAt = Datatype->attributedAt.ToUnixTimestamp(),
		.campaignId = ConvertFStringToCharPtr(Datatype->campaignId),
		.platform = ConvertFStringToCharPtr(Datatype->platform)
	};

	return ConvertedType;
}

TSharedPtr<const FPFContactEmailInfoModel> ConvertContactEmailInfoModelToUnreal(const PFContactEmailInfoModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFContactEmailInfoModel> ConvertedType = MakeShared<FPFContactEmailInfoModel>(FPFContactEmailInfoModel{
		.emailAddress = Datatype->emailAddress == nullptr ? FString() : FString(Datatype->emailAddress),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.verificationStatus = MakeShared<FPFEmailVerificationStatus>(ConvertEmailVerificationStatusToUnreal(Datatype->verificationStatus))
	});

	return ConvertedType;
}

const PFContactEmailInfoModel* ConvertContactEmailInfoModelToPlayfab(TSharedPtr<const FPFContactEmailInfoModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFContactEmailInfoModel* ConvertedType = new PFContactEmailInfoModel{
		.emailAddress = ConvertFStringToCharPtr(Datatype->emailAddress),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.verificationStatus = new PFEmailVerificationStatus(ConvertEmailVerificationStatusToPlayfab(Datatype->verificationStatus))
	};

	return ConvertedType;
}

TSharedPtr<const FPFLinkedPlatformAccountModel> ConvertLinkedPlatformAccountModelToUnreal(const PFLinkedPlatformAccountModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLinkedPlatformAccountModel> ConvertedType = MakeShared<FPFLinkedPlatformAccountModel>(FPFLinkedPlatformAccountModel{
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.platform = MakeShared<FPFLoginIdentityProvider>(ConvertLoginIdentityProviderToUnreal(Datatype->platform)),
		.platformUserId = Datatype->platformUserId == nullptr ? FString() : FString(Datatype->platformUserId),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFLinkedPlatformAccountModel* ConvertLinkedPlatformAccountModelToPlayfab(TSharedPtr<const FPFLinkedPlatformAccountModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLinkedPlatformAccountModel* ConvertedType = new PFLinkedPlatformAccountModel{
		.email = ConvertFStringToCharPtr(Datatype->email),
		.platform = new PFLoginIdentityProvider(ConvertLoginIdentityProviderToPlayfab(Datatype->platform)),
		.platformUserId = ConvertFStringToCharPtr(Datatype->platformUserId),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLocationModel> ConvertLocationModelToUnreal(const PFLocationModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLocationModel> ConvertedType = MakeShared<FPFLocationModel>(FPFLocationModel{
		.city = Datatype->city == nullptr ? FString() : FString(Datatype->city),
		.continentCode = MakeShared<FPFContinentCode>(ConvertContinentCodeToUnreal(Datatype->continentCode)),
		.countryCode = MakeShared<FPFCountryCode>(ConvertCountryCodeToUnreal(Datatype->countryCode)),
		.latitude = TSharedPtr<const double>(Datatype->latitude),
		.longitude = TSharedPtr<const double>(Datatype->longitude)
	});

	return ConvertedType;
}

const PFLocationModel* ConvertLocationModelToPlayfab(TSharedPtr<const FPFLocationModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLocationModel* ConvertedType = new PFLocationModel{
		.city = ConvertFStringToCharPtr(Datatype->city),
		.continentCode = new PFContinentCode(ConvertContinentCodeToPlayfab(Datatype->continentCode)),
		.countryCode = new PFCountryCode(ConvertCountryCodeToPlayfab(Datatype->countryCode)),
		.latitude = new double(*Datatype->latitude),
		.longitude = new double(*Datatype->longitude)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSubscriptionModel> ConvertSubscriptionModelToUnreal(const PFSubscriptionModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSubscriptionModel> ConvertedType = MakeShared<FPFSubscriptionModel>(FPFSubscriptionModel{
		.expiration = FDateTime::FromUnixTimestamp((int64)Datatype->expiration),
		.initialSubscriptionTime = FDateTime::FromUnixTimestamp((int64)Datatype->initialSubscriptionTime),
		.isActive = Datatype->isActive,
		.status = MakeShared<FPFSubscriptionProviderStatus>(ConvertSubscriptionProviderStatusToUnreal(Datatype->status)),
		.subscriptionId = Datatype->subscriptionId == nullptr ? FString() : FString(Datatype->subscriptionId),
		.subscriptionItemId = Datatype->subscriptionItemId == nullptr ? FString() : FString(Datatype->subscriptionItemId),
		.subscriptionProvider = Datatype->subscriptionProvider == nullptr ? FString() : FString(Datatype->subscriptionProvider)
	});

	return ConvertedType;
}

const PFSubscriptionModel* ConvertSubscriptionModelToPlayfab(TSharedPtr<const FPFSubscriptionModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSubscriptionModel* ConvertedType = new PFSubscriptionModel{
		.expiration = Datatype->expiration.ToUnixTimestamp(),
		.initialSubscriptionTime = Datatype->initialSubscriptionTime.ToUnixTimestamp(),
		.isActive = Datatype->isActive,
		.status = new PFSubscriptionProviderStatus(ConvertSubscriptionProviderStatusToPlayfab(Datatype->status)),
		.subscriptionId = ConvertFStringToCharPtr(Datatype->subscriptionId),
		.subscriptionItemId = ConvertFStringToCharPtr(Datatype->subscriptionItemId),
		.subscriptionProvider = ConvertFStringToCharPtr(Datatype->subscriptionProvider)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMembershipModel> ConvertMembershipModelToUnreal(const PFMembershipModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMembershipModel> ConvertedType = MakeShared<FPFMembershipModel>(FPFMembershipModel{
		.isActive = Datatype->isActive,
		.membershipExpiration = FDateTime::FromUnixTimestamp((int64)Datatype->membershipExpiration),
		.membershipId = Datatype->membershipId == nullptr ? FString() : FString(Datatype->membershipId),
		.overrideExpiration = ConvertTimeToUnreal(Datatype->overrideExpiration),
		.subscriptions = ConvertPlayfabArrayToUnreal(Datatype->subscriptions, Datatype->subscriptionsCount, ConvertSubscriptionModelToUnreal),
		.subscriptionsCount = Datatype->subscriptionsCount
	});

	return ConvertedType;
}

const PFMembershipModel* ConvertMembershipModelToPlayfab(TSharedPtr<const FPFMembershipModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMembershipModel* ConvertedType = new PFMembershipModel{
		.isActive = Datatype->isActive,
		.membershipExpiration = Datatype->membershipExpiration.ToUnixTimestamp(),
		.membershipId = ConvertFStringToCharPtr(Datatype->membershipId),
		.overrideExpiration = ConvertFDateTimeToPlayfab(Datatype->overrideExpiration),
		.subscriptions = ConvertUnrealArrayToPlayfab(Datatype->subscriptions, ConvertSubscriptionModelToPlayfab),
		.subscriptionsCount = (uint32_t)Datatype->subscriptions.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPushNotificationRegistrationModel> ConvertPushNotificationRegistrationModelToUnreal(const PFPushNotificationRegistrationModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPushNotificationRegistrationModel> ConvertedType = MakeShared<FPFPushNotificationRegistrationModel>(FPFPushNotificationRegistrationModel{
		.notificationEndpointARN = Datatype->notificationEndpointARN == nullptr ? FString() : FString(Datatype->notificationEndpointARN),
		.platform = MakeShared<FPFPushNotificationPlatform>(ConvertPushNotificationPlatformToUnreal(Datatype->platform))
	});

	return ConvertedType;
}

const PFPushNotificationRegistrationModel* ConvertPushNotificationRegistrationModelToPlayfab(TSharedPtr<const FPFPushNotificationRegistrationModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPushNotificationRegistrationModel* ConvertedType = new PFPushNotificationRegistrationModel{
		.notificationEndpointARN = ConvertFStringToCharPtr(Datatype->notificationEndpointARN),
		.platform = new PFPushNotificationPlatform(ConvertPushNotificationPlatformToPlayfab(Datatype->platform))
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticModel> ConvertStatisticModelToUnreal(const PFStatisticModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticModel> ConvertedType = MakeShared<FPFStatisticModel>(FPFStatisticModel{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.value = Datatype->value,
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFStatisticModel* ConvertStatisticModelToPlayfab(TSharedPtr<const FPFStatisticModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticModel* ConvertedType = new PFStatisticModel{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.value = Datatype->value,
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFTagModel> ConvertTagModelToUnreal(const PFTagModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTagModel> ConvertedType = MakeShared<FPFTagModel>(FPFTagModel{
		.tagValue = Datatype->tagValue == nullptr ? FString() : FString(Datatype->tagValue)
	});

	return ConvertedType;
}

const PFTagModel* ConvertTagModelToPlayfab(TSharedPtr<const FPFTagModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTagModel* ConvertedType = new PFTagModel{
		.tagValue = ConvertFStringToCharPtr(Datatype->tagValue)
	};

	return ConvertedType;
}

TSharedPtr<const FPFValueToDateModel> ConvertValueToDateModelToUnreal(const PFValueToDateModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFValueToDateModel> ConvertedType = MakeShared<FPFValueToDateModel>(FPFValueToDateModel{
		.currency = Datatype->currency == nullptr ? FString() : FString(Datatype->currency),
		.totalValue = Datatype->totalValue,
		.totalValueAsDecimal = Datatype->totalValueAsDecimal == nullptr ? FString() : FString(Datatype->totalValueAsDecimal)
	});

	return ConvertedType;
}

const PFValueToDateModel* ConvertValueToDateModelToPlayfab(TSharedPtr<const FPFValueToDateModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFValueToDateModel* ConvertedType = new PFValueToDateModel{
		.currency = ConvertFStringToCharPtr(Datatype->currency),
		.totalValue = Datatype->totalValue,
		.totalValueAsDecimal = ConvertFStringToCharPtr(Datatype->totalValueAsDecimal)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerProfileModel> ConvertPlayerProfileModelToUnreal(const PFPlayerProfileModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerProfileModel> ConvertedType = MakeShared<FPFPlayerProfileModel>(FPFPlayerProfileModel{
		.adCampaignAttributions = ConvertPlayfabArrayToUnreal(Datatype->adCampaignAttributions, Datatype->adCampaignAttributionsCount, ConvertAdCampaignAttributionModelToUnreal),
		.adCampaignAttributionsCount = Datatype->adCampaignAttributionsCount,
		.avatarUrl = Datatype->avatarUrl == nullptr ? FString() : FString(Datatype->avatarUrl),
		.bannedUntil = ConvertTimeToUnreal(Datatype->bannedUntil),
		.contactEmailAddresses = ConvertPlayfabArrayToUnreal(Datatype->contactEmailAddresses, Datatype->contactEmailAddressesCount, ConvertContactEmailInfoModelToUnreal),
		.contactEmailAddressesCount = Datatype->contactEmailAddressesCount,
		.created = ConvertTimeToUnreal(Datatype->created),
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.experimentVariants = ConvertCharArrayToUnreal(Datatype->experimentVariants, Datatype->experimentVariantsCount),
		.experimentVariantsCount = Datatype->experimentVariantsCount,
		.lastLogin = ConvertTimeToUnreal(Datatype->lastLogin),
		.linkedAccounts = ConvertPlayfabArrayToUnreal(Datatype->linkedAccounts, Datatype->linkedAccountsCount, ConvertLinkedPlatformAccountModelToUnreal),
		.linkedAccountsCount = Datatype->linkedAccountsCount,
		.locations = ConvertPlayfabArrayToUnreal(Datatype->locations, Datatype->locationsCount, ConvertLocationModelToUnreal),
		.locationsCount = Datatype->locationsCount,
		.memberships = ConvertPlayfabArrayToUnreal(Datatype->memberships, Datatype->membershipsCount, ConvertMembershipModelToUnreal),
		.membershipsCount = Datatype->membershipsCount,
		.origination = MakeShared<FPFLoginIdentityProvider>(ConvertLoginIdentityProviderToUnreal(Datatype->origination)),
		.playerId = Datatype->playerId == nullptr ? FString() : FString(Datatype->playerId),
		.publisherId = Datatype->publisherId == nullptr ? FString() : FString(Datatype->publisherId),
		.pushNotificationRegistrations = ConvertPlayfabArrayToUnreal(Datatype->pushNotificationRegistrations, Datatype->pushNotificationRegistrationsCount, ConvertPushNotificationRegistrationModelToUnreal),
		.pushNotificationRegistrationsCount = Datatype->pushNotificationRegistrationsCount,
		.statistics = ConvertPlayfabArrayToUnreal(Datatype->statistics, Datatype->statisticsCount, ConvertStatisticModelToUnreal),
		.statisticsCount = Datatype->statisticsCount,
		.tags = ConvertPlayfabArrayToUnreal(Datatype->tags, Datatype->tagsCount, ConvertTagModelToUnreal),
		.tagsCount = Datatype->tagsCount,
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId),
		.totalValueToDateInUSD = TSharedPtr<const uint32>(Datatype->totalValueToDateInUSD),
		.valuesToDate = ConvertPlayfabArrayToUnreal(Datatype->valuesToDate, Datatype->valuesToDateCount, ConvertValueToDateModelToUnreal),
		.valuesToDateCount = Datatype->valuesToDateCount
	});

	return ConvertedType;
}

const PFPlayerProfileModel* ConvertPlayerProfileModelToPlayfab(TSharedPtr<const FPFPlayerProfileModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerProfileModel* ConvertedType = new PFPlayerProfileModel{
		.adCampaignAttributions = ConvertUnrealArrayToPlayfab(Datatype->adCampaignAttributions, ConvertAdCampaignAttributionModelToPlayfab),
		.adCampaignAttributionsCount = (uint32_t)Datatype->adCampaignAttributions.Num(),
		.avatarUrl = ConvertFStringToCharPtr(Datatype->avatarUrl),
		.bannedUntil = ConvertFDateTimeToPlayfab(Datatype->bannedUntil),
		.contactEmailAddresses = ConvertUnrealArrayToPlayfab(Datatype->contactEmailAddresses, ConvertContactEmailInfoModelToPlayfab),
		.contactEmailAddressesCount = (uint32_t)Datatype->contactEmailAddresses.Num(),
		.created = ConvertFDateTimeToPlayfab(Datatype->created),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.experimentVariants = ConvertFStringArrayToPlayfab(Datatype->experimentVariants),
		.experimentVariantsCount = (uint32_t)Datatype->experimentVariants.Num(),
		.lastLogin = ConvertFDateTimeToPlayfab(Datatype->lastLogin),
		.linkedAccounts = ConvertUnrealArrayToPlayfab(Datatype->linkedAccounts, ConvertLinkedPlatformAccountModelToPlayfab),
		.linkedAccountsCount = (uint32_t)Datatype->linkedAccounts.Num(),
		.locations = ConvertUnrealArrayToPlayfab(Datatype->locations, ConvertLocationModelToPlayfab),
		.locationsCount = (uint32_t)Datatype->locations.Num(),
		.memberships = ConvertUnrealArrayToPlayfab(Datatype->memberships, ConvertMembershipModelToPlayfab),
		.membershipsCount = (uint32_t)Datatype->memberships.Num(),
		.origination = new PFLoginIdentityProvider(ConvertLoginIdentityProviderToPlayfab(Datatype->origination)),
		.playerId = ConvertFStringToCharPtr(Datatype->playerId),
		.publisherId = ConvertFStringToCharPtr(Datatype->publisherId),
		.pushNotificationRegistrations = ConvertUnrealArrayToPlayfab(Datatype->pushNotificationRegistrations, ConvertPushNotificationRegistrationModelToPlayfab),
		.pushNotificationRegistrationsCount = (uint32_t)Datatype->pushNotificationRegistrations.Num(),
		.statistics = ConvertUnrealArrayToPlayfab(Datatype->statistics, ConvertStatisticModelToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num(),
		.tags = ConvertUnrealArrayToPlayfab(Datatype->tags, ConvertTagModelToPlayfab),
		.tagsCount = (uint32_t)Datatype->tags.Num(),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId),
		.totalValueToDateInUSD = new uint32(*Datatype->totalValueToDateInUSD),
		.valuesToDate = ConvertUnrealArrayToPlayfab(Datatype->valuesToDate, ConvertValueToDateModelToPlayfab),
		.valuesToDateCount = (uint32_t)Datatype->valuesToDate.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> ConvertGetPlayerCombinedInfoRequestParamsToUnreal(const PFGetPlayerCombinedInfoRequestParams* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> ConvertedType = MakeShared<FPFGetPlayerCombinedInfoRequestParams>(FPFGetPlayerCombinedInfoRequestParams{
		.getCharacterInventories = Datatype->getCharacterInventories,
		.getCharacterList = Datatype->getCharacterList,
		.getPlayerProfile = Datatype->getPlayerProfile,
		.getPlayerStatistics = Datatype->getPlayerStatistics,
		.getTitleData = Datatype->getTitleData,
		.getUserAccountInfo = Datatype->getUserAccountInfo,
		.getUserData = Datatype->getUserData,
		.getUserInventory = Datatype->getUserInventory,
		.getUserReadOnlyData = Datatype->getUserReadOnlyData,
		.getUserVirtualCurrency = Datatype->getUserVirtualCurrency,
		.playerStatisticNames = ConvertCharArrayToUnreal(Datatype->playerStatisticNames, Datatype->playerStatisticNamesCount),
		.playerStatisticNamesCount = Datatype->playerStatisticNamesCount,
		.profileConstraints = ConvertPlayerProfileViewConstraintsToUnreal(Datatype->profileConstraints),
		.titleDataKeys = ConvertCharArrayToUnreal(Datatype->titleDataKeys, Datatype->titleDataKeysCount),
		.titleDataKeysCount = Datatype->titleDataKeysCount,
		.userDataKeys = ConvertCharArrayToUnreal(Datatype->userDataKeys, Datatype->userDataKeysCount),
		.userDataKeysCount = Datatype->userDataKeysCount,
		.userReadOnlyDataKeys = ConvertCharArrayToUnreal(Datatype->userReadOnlyDataKeys, Datatype->userReadOnlyDataKeysCount),
		.userReadOnlyDataKeysCount = Datatype->userReadOnlyDataKeysCount
	});

	return ConvertedType;
}

const PFGetPlayerCombinedInfoRequestParams* ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGetPlayerCombinedInfoRequestParams* ConvertedType = new PFGetPlayerCombinedInfoRequestParams{
		.getCharacterInventories = Datatype->getCharacterInventories,
		.getCharacterList = Datatype->getCharacterList,
		.getPlayerProfile = Datatype->getPlayerProfile,
		.getPlayerStatistics = Datatype->getPlayerStatistics,
		.getTitleData = Datatype->getTitleData,
		.getUserAccountInfo = Datatype->getUserAccountInfo,
		.getUserData = Datatype->getUserData,
		.getUserInventory = Datatype->getUserInventory,
		.getUserReadOnlyData = Datatype->getUserReadOnlyData,
		.getUserVirtualCurrency = Datatype->getUserVirtualCurrency,
		.playerStatisticNames = ConvertFStringArrayToPlayfab(Datatype->playerStatisticNames),
		.playerStatisticNamesCount = (uint32_t)Datatype->playerStatisticNames.Num(),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Datatype->profileConstraints),
		.titleDataKeys = ConvertFStringArrayToPlayfab(Datatype->titleDataKeys),
		.titleDataKeysCount = (uint32_t)Datatype->titleDataKeys.Num(),
		.userDataKeys = ConvertFStringArrayToPlayfab(Datatype->userDataKeys),
		.userDataKeysCount = (uint32_t)Datatype->userDataKeys.Num(),
		.userReadOnlyDataKeys = ConvertFStringArrayToPlayfab(Datatype->userReadOnlyDataKeys),
		.userReadOnlyDataKeysCount = (uint32_t)Datatype->userReadOnlyDataKeys.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCharacterInventory> ConvertCharacterInventoryToUnreal(const PFCharacterInventory* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCharacterInventory> ConvertedType = MakeShared<FPFCharacterInventory>(FPFCharacterInventory{
		.characterId = Datatype->characterId == nullptr ? FString() : FString(Datatype->characterId),
		.inventory = ConvertPlayfabArrayToUnreal(Datatype->inventory, Datatype->inventoryCount, ConvertItemInstanceToUnreal),
		.inventoryCount = Datatype->inventoryCount
	});

	return ConvertedType;
}

const PFCharacterInventory* ConvertCharacterInventoryToPlayfab(TSharedPtr<const FPFCharacterInventory> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCharacterInventory* ConvertedType = new PFCharacterInventory{
		.characterId = ConvertFStringToCharPtr(Datatype->characterId),
		.inventory = ConvertUnrealArrayToPlayfab(Datatype->inventory, ConvertItemInstanceToPlayfab),
		.inventoryCount = (uint32_t)Datatype->inventory.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticValue> ConvertStatisticValueToUnreal(const PFStatisticValue* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticValue> ConvertedType = MakeShared<FPFStatisticValue>(FPFStatisticValue{
		.statisticName = Datatype->statisticName == nullptr ? FString() : FString(Datatype->statisticName),
		.value = Datatype->value,
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFStatisticValue* ConvertStatisticValueToPlayfab(TSharedPtr<const FPFStatisticValue> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticValue* ConvertedType = new PFStatisticValue{
		.statisticName = ConvertFStringToCharPtr(Datatype->statisticName),
		.value = Datatype->value,
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> ConvertGetPlayerCombinedInfoResultPayloadToUnreal(const PFGetPlayerCombinedInfoResultPayload* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> ConvertedType = MakeShared<FPFGetPlayerCombinedInfoResultPayload>(FPFGetPlayerCombinedInfoResultPayload{
		.accountInfo = ConvertUserAccountInfoToUnreal(Datatype->accountInfo),
		.characterInventories = ConvertPlayfabArrayToUnreal(Datatype->characterInventories, Datatype->characterInventoriesCount, ConvertCharacterInventoryToUnreal),
		.characterInventoriesCount = Datatype->characterInventoriesCount,
		.characterList = ConvertPlayfabArrayToUnreal(Datatype->characterList, Datatype->characterListCount, ConvertCharacterResultToUnreal),
		.characterListCount = Datatype->characterListCount,
		.playerProfile = ConvertPlayerProfileModelToUnreal(Datatype->playerProfile),
		.playerStatistics = ConvertPlayfabArrayToUnreal(Datatype->playerStatistics, Datatype->playerStatisticsCount, ConvertStatisticValueToUnreal),
		.playerStatisticsCount = Datatype->playerStatisticsCount,
		.titleData = ConvertCharMapToUnreal(Datatype->titleData, Datatype->titleDataCount),
		.titleDataCount = Datatype->titleDataCount,
		.userData = ConvertPlayfabMapToUnreal<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->userData, Datatype->userDataCount, ConvertUserDataRecordToUnreal),
		.userDataCount = Datatype->userDataCount,
		.userDataVersion = Datatype->userDataVersion,
		.userInventory = ConvertPlayfabArrayToUnreal(Datatype->userInventory, Datatype->userInventoryCount, ConvertItemInstanceToUnreal),
		.userInventoryCount = Datatype->userInventoryCount,
		.userReadOnlyData = ConvertPlayfabMapToUnreal<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->userReadOnlyData, Datatype->userReadOnlyDataCount, ConvertUserDataRecordToUnreal),
		.userReadOnlyDataCount = Datatype->userReadOnlyDataCount,
		.userReadOnlyDataVersion = Datatype->userReadOnlyDataVersion,
		.userVirtualCurrency = ConvertIntMapToUnreal(Datatype->userVirtualCurrency, Datatype->userVirtualCurrencyCount),
		.userVirtualCurrencyCount = Datatype->userVirtualCurrencyCount,
		.userVirtualCurrencyRechargeTimes = ConvertPlayfabMapToUnreal<PFVirtualCurrencyRechargeTimeDictionaryEntry, FPFVirtualCurrencyRechargeTime, PFVirtualCurrencyRechargeTime>(Datatype->userVirtualCurrencyRechargeTimes, Datatype->userVirtualCurrencyRechargeTimesCount, ConvertVirtualCurrencyRechargeTimeToUnreal),
		.userVirtualCurrencyRechargeTimesCount = Datatype->userVirtualCurrencyRechargeTimesCount
	});

	return ConvertedType;
}

const PFGetPlayerCombinedInfoResultPayload* ConvertGetPlayerCombinedInfoResultPayloadToPlayfab(TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGetPlayerCombinedInfoResultPayload* ConvertedType = new PFGetPlayerCombinedInfoResultPayload{
		.accountInfo = ConvertUserAccountInfoToPlayfab(Datatype->accountInfo),
		.characterInventories = ConvertUnrealArrayToPlayfab(Datatype->characterInventories, ConvertCharacterInventoryToPlayfab),
		.characterInventoriesCount = (uint32_t)Datatype->characterInventories.Num(),
		.characterList = ConvertUnrealArrayToPlayfab(Datatype->characterList, ConvertCharacterResultToPlayfab),
		.characterListCount = (uint32_t)Datatype->characterList.Num(),
		.playerProfile = ConvertPlayerProfileModelToPlayfab(Datatype->playerProfile),
		.playerStatistics = ConvertUnrealArrayToPlayfab(Datatype->playerStatistics, ConvertStatisticValueToPlayfab),
		.playerStatisticsCount = (uint32_t)Datatype->playerStatistics.Num(),
		.titleData = ConvertFStringMapToPlayfab(Datatype->titleData),
		.titleDataCount = (uint32_t)Datatype->titleData.Num(),
		.userData = ConvertUnrealMapToPlayfab<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->userData, ConvertUserDataRecordToPlayfab),
		.userDataCount = (uint32_t)Datatype->userData.Num(),
		.userDataVersion = Datatype->userDataVersion,
		.userInventory = ConvertUnrealArrayToPlayfab(Datatype->userInventory, ConvertItemInstanceToPlayfab),
		.userInventoryCount = (uint32_t)Datatype->userInventory.Num(),
		.userReadOnlyData = ConvertUnrealMapToPlayfab<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->userReadOnlyData, ConvertUserDataRecordToPlayfab),
		.userReadOnlyDataCount = (uint32_t)Datatype->userReadOnlyData.Num(),
		.userReadOnlyDataVersion = Datatype->userReadOnlyDataVersion,
		.userVirtualCurrency = ConvertIntMapToPlayfab(Datatype->userVirtualCurrency),
		.userVirtualCurrencyCount = (uint32_t)Datatype->userVirtualCurrency.Num(),
		.userVirtualCurrencyRechargeTimes = ConvertUnrealMapToPlayfab<PFVirtualCurrencyRechargeTimeDictionaryEntry, FPFVirtualCurrencyRechargeTime, PFVirtualCurrencyRechargeTime>(Datatype->userVirtualCurrencyRechargeTimes, ConvertVirtualCurrencyRechargeTimeToPlayfab),
		.userVirtualCurrencyRechargeTimesCount = (uint32_t)Datatype->userVirtualCurrencyRechargeTimes.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFVariable> ConvertVariableToUnreal(const PFVariable* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFVariable> ConvertedType = MakeShared<FPFVariable>(FPFVariable{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFVariable* ConvertVariableToPlayfab(TSharedPtr<const FPFVariable> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFVariable* ConvertedType = new PFVariable{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}

TSharedPtr<const FPFTreatmentAssignment> ConvertTreatmentAssignmentToUnreal(const PFTreatmentAssignment* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTreatmentAssignment> ConvertedType = MakeShared<FPFTreatmentAssignment>(FPFTreatmentAssignment{
		.variables = ConvertPlayfabArrayToUnreal(Datatype->variables, Datatype->variablesCount, ConvertVariableToUnreal),
		.variablesCount = Datatype->variablesCount,
		.variants = ConvertCharArrayToUnreal(Datatype->variants, Datatype->variantsCount),
		.variantsCount = Datatype->variantsCount
	});

	return ConvertedType;
}

const PFTreatmentAssignment* ConvertTreatmentAssignmentToPlayfab(TSharedPtr<const FPFTreatmentAssignment> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTreatmentAssignment* ConvertedType = new PFTreatmentAssignment{
		.variables = ConvertUnrealArrayToPlayfab(Datatype->variables, ConvertVariableToPlayfab),
		.variablesCount = (uint32_t)Datatype->variables.Num(),
		.variants = ConvertFStringArrayToPlayfab(Datatype->variants),
		.variantsCount = (uint32_t)Datatype->variants.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFEntityLineage> ConvertEntityLineageToUnreal(const PFEntityLineage* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEntityLineage> ConvertedType = MakeShared<FPFEntityLineage>(FPFEntityLineage{
		.characterId = Datatype->characterId == nullptr ? FString() : FString(Datatype->characterId),
		.groupId = Datatype->groupId == nullptr ? FString() : FString(Datatype->groupId),
		.masterPlayerAccountId = Datatype->masterPlayerAccountId == nullptr ? FString() : FString(Datatype->masterPlayerAccountId),
		.namespaceId = Datatype->namespaceId == nullptr ? FString() : FString(Datatype->namespaceId),
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId),
		.titlePlayerAccountId = Datatype->titlePlayerAccountId == nullptr ? FString() : FString(Datatype->titlePlayerAccountId)
	});

	return ConvertedType;
}

const PFEntityLineage* ConvertEntityLineageToPlayfab(TSharedPtr<const FPFEntityLineage> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEntityLineage* ConvertedType = new PFEntityLineage{
		.characterId = ConvertFStringToCharPtr(Datatype->characterId),
		.groupId = ConvertFStringToCharPtr(Datatype->groupId),
		.masterPlayerAccountId = ConvertFStringToCharPtr(Datatype->masterPlayerAccountId),
		.namespaceId = ConvertFStringToCharPtr(Datatype->namespaceId),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId),
		.titlePlayerAccountId = ConvertFStringToCharPtr(Datatype->titlePlayerAccountId)
	};

	return ConvertedType;
}


const char* ConvertFStringToCharPtr(const FString UnrealString)
{
	if (UnrealString.IsEmpty())
	{
		return nullptr;
	}

    FTCHARToUTF8 Converted(*UnrealString);
    char* ConvertedString = new char[Converted.Length() + 1];
    FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
    ConvertedString[Converted.Length()] = '\0';

	return ConvertedString;
}

TArray<FString> ConvertCharArrayToUnreal(const char* const* Array, int32 ArraySize)
{
	if (Array == nullptr)
	{
		return TArray<FString>();
	}

	TArray<FString> ConvertedArray;
	ConvertedArray.Reserve(ArraySize);
	for (int32 i = 0; i < ArraySize; ++i) {
		ConvertedArray.Add(FString(Array[i]));
	}
	return ConvertedArray;
}

const char* const* ConvertFStringArrayToPlayfab(const TArray<FString> Array)
{
	if (Array.Num() == 0)
	{
		return nullptr;
	}

	static TArray<const char*> ConvertedArray;
	for (const char* Ptr : ConvertedArray)
	{
		delete[] Ptr;
	}
	ConvertedArray.Reset();
    
	ConvertedArray.Reserve(Array.Num());
	for (int32 i = 0; i < Array.Num(); ++i) {
        FTCHARToUTF8 Converted(*Array[i]);
        char* ConvertedString = new char[Converted.Length() + 1];
        FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
        ConvertedString[Converted.Length()] = '\0';
		
		ConvertedArray.Add(ConvertedString);
	}
	return ConvertedArray.GetData();
}

TArray<FDateTime> ConvertTimeArrayToUnreal(const time_t* const* Array, int32 ArraySize)
{
	if (Array == nullptr)
	{
		return TArray<FDateTime>();
	}

	TArray<FDateTime> ConvertedArray;
	ConvertedArray.Reserve(ArraySize);
	for (int32 i = 0; i < ArraySize; ++i) {
		ConvertedArray.Add(FDateTime::FromUnixTimestamp((int64)Array[i]));
	}
	return ConvertedArray;
}

const time_t* const* ConvertFDateTimeArrayToPlayfab(TArray<FDateTime> Array)
{
	if (Array.Num() == 0)
	{
		return nullptr;
	}

	time_t** ConvertedArray = new time_t*[Array.Num()];
	for (int32 i = 0; i < Array.Num(); ++i) {
		ConvertedArray[i] = new time_t(Array[i].ToUnixTimestamp());
	}
	return ConvertedArray;
}

TMap<const FString, uint32> ConvertUintMapToUnreal(const PFUint32DictionaryEntry* Map, int32 MapSize)
{
	if (Map == nullptr)
	{
		return TMap<const FString, uint32>();
	}

	TMap<const FString, uint32> ConvertedMap;
	for (int32 i = 0; i < MapSize; ++i)
	{
		ConvertedMap.Add(FString(Map[i].key), Map[i].value);
	}
	return ConvertedMap;
}

const PFUint32DictionaryEntry* ConvertUintMapToPlayfab(TMap<const FString, uint32> Map)
{
	if (Map.Num() == 0)
	{
		return nullptr;
	}

	PFUint32DictionaryEntry* ConvertedMap = new PFUint32DictionaryEntry[Map.Num()];
	int32 i = 0;
	for (auto Pair = Map.CreateConstIterator(); Pair; ++Pair)
	{
        FTCHARToUTF8 Converted(*Pair.Key());
        char* ConvertedString = new char[Converted.Length() + 1];
        FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
        ConvertedString[Converted.Length()] = '\0';

		PFUint32DictionaryEntry* ConvertedItem = new PFUint32DictionaryEntry{
			.key = ConvertedString,
			.value = Pair.Value()
		};
		ConvertedMap[i] = *ConvertedItem;
        ++i;
    }
    return ConvertedMap;
}

TMap<const FString, int32> ConvertIntMapToUnreal(const PFInt32DictionaryEntry* Map, int32 MapSize)
{
    if (Map == nullptr)
    {
        return TMap<const FString, int32>();
    }

    TMap<const FString, int32> ConvertedMap;
    for (int32 i = 0; i < MapSize; ++i)
    {
        ConvertedMap.Add(FString(Map[i].key), Map[i].value);
    }
    return ConvertedMap;
}

const PFInt32DictionaryEntry* ConvertIntMapToPlayfab(TMap<const FString, int32> Map)
{
    if (Map.Num() == 0)
    {
        return nullptr;
    }

    PFInt32DictionaryEntry* ConvertedMap = new PFInt32DictionaryEntry[Map.Num()];
    int32 i = 0;
    for (auto Pair = Map.CreateConstIterator(); Pair; ++Pair)
    {
        FTCHARToUTF8 Converted(*Pair.Key());
        char* ConvertedString = new char[Converted.Length() + 1];
        FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
        ConvertedString[Converted.Length()] = '\0';

        PFInt32DictionaryEntry* ConvertedItem = new PFInt32DictionaryEntry{
            .key = ConvertedString,
            .value = Pair.Value()
        };
        ConvertedMap[i] = *ConvertedItem;
        ++i;
    }
    return ConvertedMap;
}

TMap<const FString, const FString> ConvertCharMapToUnreal(const PFStringDictionaryEntry* Map, int32 MapSize)
{
    if (Map == nullptr)
    {
        return TMap<const FString, const FString>();
    }

    TMap<const FString, const FString> ConvertedMap;
    for (int32 i = 0; i < MapSize; ++i)
    {
        ConvertedMap.Add(FString(Map[i].key), FString(Map[i].value));
    }
    return ConvertedMap;
}

const PFStringDictionaryEntry* ConvertFStringMapToPlayfab(TMap<const FString, const FString> Map)
{
    if (Map.Num() == 0)
    {
        return nullptr;
    }

    PFStringDictionaryEntry* ConvertedMap = new PFStringDictionaryEntry[Map.Num()];
    int32 i = 0;
    for (auto Pair = Map.CreateConstIterator(); Pair; ++Pair)
    {
        FTCHARToUTF8 ConvertedKey(*Pair.Key());
        char* ConvertedStringKey = new char[ConvertedKey.Length() + 1];
        FMemory::Memcpy(ConvertedStringKey, ConvertedKey.Get(), ConvertedKey.Length());
        ConvertedStringKey[ConvertedKey.Length()] = '\0';

        FTCHARToUTF8 Converted(*Pair.Value());
        char* ConvertedString = new char[Converted.Length() + 1];
        FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
        ConvertedString[Converted.Length()] = '\0';

        PFStringDictionaryEntry* ConvertedItem = new PFStringDictionaryEntry{
            .key = ConvertedStringKey,
            .value = ConvertedString
        };
        ConvertedMap[i] = *ConvertedItem;
        ++i;
    }
    return ConvertedMap;
}

TMap<const FString, const FDateTime> ConvertTimeMapToUnreal(const PFDateTimeDictionaryEntry* Map, int32 MapSize)
{
    if (Map == nullptr)
    {
        return TMap<const FString, const FDateTime>();
    }

    TMap<const FString, const FDateTime> ConvertedMap;
    for (int32 i = 0; i < MapSize; ++i)
    {
        ConvertedMap.Add(FString(Map[i].key), FDateTime::FromUnixTimestamp((int64)Map[i].value));
    }
    return ConvertedMap;
}

const PFDateTimeDictionaryEntry* ConvertFDateTimeMapToPlayfab(TMap<const FString, const FDateTime> Map)
{
    if (Map.Num() == 0)
    {
        return nullptr;
    }

    PFDateTimeDictionaryEntry* ConvertedMap = new PFDateTimeDictionaryEntry[Map.Num()];
    int32 i = 0;
    for (auto Pair = Map.CreateConstIterator(); Pair; ++Pair)
    {
        FTCHARToUTF8 Converted(*Pair.Key());
        char* ConvertedString = new char[Converted.Length() + 1];
        FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
        ConvertedString[Converted.Length()] = '\0';

        PFDateTimeDictionaryEntry* ConvertedItem = new PFDateTimeDictionaryEntry{
            .key = ConvertedString,
            .value = Pair.Value().ToUnixTimestamp()
        };
        ConvertedMap[i] = *ConvertedItem;
        ++i;
    }
    return ConvertedMap;
}

const time_t* ConvertFDateTimeToPlayfab(TSharedPtr<const FDateTime> Time)
{
    const time_t* ConvertedTime = new time_t(Time->ToUnixTimestamp());
    return ConvertedTime;
}

TSharedPtr<const FDateTime> ConvertTimeToUnreal(const time_t* Time)
{
    TSharedPtr<const FDateTime> ConvertedTime = MakeShared<FDateTime>(FDateTime::FromUnixTimestamp((int64)Time));
    return ConvertedTime;
}

const PFEntityKey* ConvertEntityKeyToPlayfab(TSharedPtr<const FPFEntityKey> Datatype) {
    if (!Datatype.IsValid())
    {
        return nullptr;
    }

    FTCHARToUTF8 ConvertedKey(*Datatype->id);
    char* ConvertedStringKey = new char[ConvertedKey.Length() + 1];
    FMemory::Memcpy(ConvertedStringKey, ConvertedKey.Get(), ConvertedKey.Length());
    ConvertedStringKey[ConvertedKey.Length()] = '\0';

    FTCHARToUTF8 Converted(*Datatype->type);
    char* ConvertedString = new char[Converted.Length() + 1];
    FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
    ConvertedString[Converted.Length()] = '\0';

    const PFEntityKey* ConvertedType = new PFEntityKey{
        .id = ConvertedStringKey,
        .type = ConvertedString
    };

    return ConvertedType;
}

TSharedPtr<const FPFEntityKey> ConvertEntityKeyToUnreal(const PFEntityKey* Datatype) {
    if (Datatype == nullptr)
    {
        return nullptr;
    }

    TSharedPtr<const FPFEntityKey> ConvertedType = MakeShared<FPFEntityKey>(FPFEntityKey{
        .id = FString(Datatype->id),
        .type = FString(Datatype->type)
        });

    return ConvertedType;
}

#pragma pop_macro("IN")
