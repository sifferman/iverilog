#ifndef IVL_PTimingCheck_H
#define IVL_PTimingCheck_H
/*
 * Copyright (c) 2006-2023 Stephen Williams <steve@icarus.com>
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

# include  "LineInfo.h"
# include  "pform_types.h"

// TODO cleanup in destructor and cleanup in Module!

/*
* The PTimingCheck is the base class for all timing checks
*/
class PTimingCheck  : public LineInfo {

    public:
      enum EdgeType {EDGE_01, EDGE_0X, EDGE_10, EDGE_1X, EDGE_X0, EDGE_X1};

      struct event_t {
        pform_name_t name;
        bool posedge;
        bool negedge;
        std::vector<EdgeType> edges;
        PExpr* condition;
      };

      PTimingCheck() { }
      virtual ~PTimingCheck() { }

      virtual void elaborate(class Design*des, class NetScope*scope) const = 0;

      virtual void dump(std::ostream&out, unsigned ind) const = 0;
};

/*
* The PRecRem is the parse of a $recrem timing check
*/
class PRecRem : public PTimingCheck {

    public:
      PRecRem(event_t reference_event,
                    event_t data_event,
                    //PExpr setup_limit,
                    //PExpr hold_limit,
                    pform_name_t* notifier,
                    pform_name_t* timestamp_cond,
                    pform_name_t* timecheck_cond,
                    pform_name_t* delayed_reference,
                    pform_name_t* delayed_data);

      ~PRecRem();

      void elaborate(class Design*des, class NetScope*scope) const override;

      void dump(std::ostream&out, unsigned ind) const override;

    public: // TODO
      event_t reference_event_; // hierarchy_identifier
      event_t data_event_;

      //PExpr setup_limit;
      //PExpr hold_limit;

      pform_name_t* notifier_;

      pform_name_t* timestamp_cond_;
      pform_name_t* timecheck_cond_;

      pform_name_t* delayed_reference_;
      pform_name_t* delayed_data_;
};

/*
* The PSetupHold is the parse of a $setuphold timing check
*/
class PSetupHold : public PTimingCheck {

    public:
      PSetupHold(event_t reference_event,
                    event_t data_event,
                    //PExpr setup_limit,
                    //PExpr hold_limit,
                    pform_name_t* notifier,
                    pform_name_t* timestamp_cond,
                    pform_name_t* timecheck_cond,
                    pform_name_t* delayed_reference,
                    pform_name_t* delayed_data);

      ~PSetupHold();

      void elaborate(class Design*des, class NetScope*scope) const override;

      void dump(std::ostream&out, unsigned ind) const override;

    public: // TODO
      event_t reference_event_; // hierarchy_identifier
      event_t data_event_;

      //PExpr setup_limit;
      //PExpr hold_limit;

      pform_name_t* notifier_;

      pform_name_t* timestamp_cond_;
      pform_name_t* timecheck_cond_;

      pform_name_t* delayed_reference_;
      pform_name_t* delayed_data_;
};

#endif /* IVL_PTimingCheck_H */
