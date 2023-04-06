#pragma once

#pragma warning(disable : 4100)

#define BIND(a_method, ...) a_vm.BindNativeMethod(obj, #a_method##sv, a_method __VA_OPT__(, ) __VA_ARGS__)

namespace Papyrus
{
	namespace Travel
	{

		inline void test(std::monostate, RE::BGSMessage* msg, std::vector<RE::TESObjectREFR*> workshops)
		{
			logger::info("this worked {:x}"sv, (uint64_t)msg);
			logger::info("this worked {}"sv, workshops.size());

			for (auto it = msg->buttonList.begin(); it != msg->buttonList.end(); ++it) {
				
				RE::MESSAGEBOX_BUTTON* msgbox = *it;
				logger::info("text: {}"sv, msgbox->text.c_str());
			}

			for (auto i : workshops) {
				if (i == nullptr) {
					continue;
				}
				RE::BGSLocation* loc = i->GetCurrentLocation();
				logger::info("location: {:x} {:x} {}"sv, (uint64_t) i, (uint64_t) loc, loc->GetFullName());
			}

		}

		inline void makeTravelMenu(std::monostate, RE::BGSMessage* msg, std::vector<RE::TESObjectREFR*> workshops)
		{
			auto it = msg->buttonList.begin();

			for (auto i = 0; i <= workshops.size(); i++) {
				++it;
			}

			msg->buttonList.erase_after(++it, msg->buttonList.end());

			it = msg->buttonList.begin();
			for (auto i : workshops) {
				RE::MESSAGEBOX_BUTTON* msgbox = *it;
				RE::BSFixedString str(i->GetCurrentLocation()->GetFullName());

				msgbox->text = str;
				msgbox->conditions.head = nullptr;
				++it;
			}

			RE::MESSAGEBOX_BUTTON* msgbox = *it;
			RE::BSFixedString str("Cancel");

			msgbox->text = str;
			msgbox->conditions.head = nullptr;
		}


		inline void F4SEAPI Bind(RE::BSScript::IVirtualMachine& a_vm)
		{

			const auto obj = "IFTNative:IFTNative"sv;
			BIND(test);
			BIND(makeTravelMenu);
			logger::info("bound {} script"sv, obj);
		}
	}
		
	inline bool F4SEAPI Bind(RE::BSScript::IVirtualMachine* a_vm) {
			if (!a_vm) {
				return false;
			}

			Travel::Bind(*a_vm);
			return true;
	}
}
