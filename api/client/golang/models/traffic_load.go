// Code generated by go-swagger; DO NOT EDIT.

package models

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"context"
	"encoding/json"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/strfmt"
	"github.com/go-openapi/swag"
	"github.com/go-openapi/validate"
)

// TrafficLoad Describes the transmit load of a packet generator
//
// swagger:model TrafficLoad
type TrafficLoad struct {

	// Tells the generator how many packets to transmit as part of an
	// atomic transmit operation. Larger burst sizes are more efficient.
	//
	// Maximum: 65535
	// Minimum: 1
	BurstSize int32 `json:"burst_size,omitempty"`

	// rate
	// Required: true
	Rate *TrafficLoadRate `json:"rate"`

	// The transmit units for the packet generator
	// Required: true
	// Enum: [frames octets]
	Units *string `json:"units"`
}

// Validate validates this traffic load
func (m *TrafficLoad) Validate(formats strfmt.Registry) error {
	var res []error

	if err := m.validateBurstSize(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateRate(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateUnits(formats); err != nil {
		res = append(res, err)
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}

func (m *TrafficLoad) validateBurstSize(formats strfmt.Registry) error {
	if swag.IsZero(m.BurstSize) { // not required
		return nil
	}

	if err := validate.MinimumInt("burst_size", "body", int64(m.BurstSize), 1, false); err != nil {
		return err
	}

	if err := validate.MaximumInt("burst_size", "body", int64(m.BurstSize), 65535, false); err != nil {
		return err
	}

	return nil
}

func (m *TrafficLoad) validateRate(formats strfmt.Registry) error {

	if err := validate.Required("rate", "body", m.Rate); err != nil {
		return err
	}

	if m.Rate != nil {
		if err := m.Rate.Validate(formats); err != nil {
			if ve, ok := err.(*errors.Validation); ok {
				return ve.ValidateName("rate")
			}
			return err
		}
	}

	return nil
}

var trafficLoadTypeUnitsPropEnum []interface{}

func init() {
	var res []string
	if err := json.Unmarshal([]byte(`["frames","octets"]`), &res); err != nil {
		panic(err)
	}
	for _, v := range res {
		trafficLoadTypeUnitsPropEnum = append(trafficLoadTypeUnitsPropEnum, v)
	}
}

const (

	// TrafficLoadUnitsFrames captures enum value "frames"
	TrafficLoadUnitsFrames string = "frames"

	// TrafficLoadUnitsOctets captures enum value "octets"
	TrafficLoadUnitsOctets string = "octets"
)

// prop value enum
func (m *TrafficLoad) validateUnitsEnum(path, location string, value string) error {
	if err := validate.EnumCase(path, location, value, trafficLoadTypeUnitsPropEnum, true); err != nil {
		return err
	}
	return nil
}

func (m *TrafficLoad) validateUnits(formats strfmt.Registry) error {

	if err := validate.Required("units", "body", m.Units); err != nil {
		return err
	}

	// value enum
	if err := m.validateUnitsEnum("units", "body", *m.Units); err != nil {
		return err
	}

	return nil
}

// ContextValidate validate this traffic load based on the context it is used
func (m *TrafficLoad) ContextValidate(ctx context.Context, formats strfmt.Registry) error {
	var res []error

	if err := m.contextValidateRate(ctx, formats); err != nil {
		res = append(res, err)
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}

func (m *TrafficLoad) contextValidateRate(ctx context.Context, formats strfmt.Registry) error {

	if m.Rate != nil {
		if err := m.Rate.ContextValidate(ctx, formats); err != nil {
			if ve, ok := err.(*errors.Validation); ok {
				return ve.ValidateName("rate")
			}
			return err
		}
	}

	return nil
}

// MarshalBinary interface implementation
func (m *TrafficLoad) MarshalBinary() ([]byte, error) {
	if m == nil {
		return nil, nil
	}
	return swag.WriteJSON(m)
}

// UnmarshalBinary interface implementation
func (m *TrafficLoad) UnmarshalBinary(b []byte) error {
	var res TrafficLoad
	if err := swag.ReadJSON(b, &res); err != nil {
		return err
	}
	*m = res
	return nil
}

// TrafficLoadRate The transmit packet rate
//
// swagger:model TrafficLoadRate
type TrafficLoadRate struct {

	// unit of time for the rate
	// Required: true
	// Enum: [second minute hour]
	Period *string `json:"period"`

	// number of packets per period
	// Required: true
	// Minimum: 1
	Value *int64 `json:"value"`
}

// Validate validates this traffic load rate
func (m *TrafficLoadRate) Validate(formats strfmt.Registry) error {
	var res []error

	if err := m.validatePeriod(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateValue(formats); err != nil {
		res = append(res, err)
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}

var trafficLoadRateTypePeriodPropEnum []interface{}

func init() {
	var res []string
	if err := json.Unmarshal([]byte(`["second","minute","hour"]`), &res); err != nil {
		panic(err)
	}
	for _, v := range res {
		trafficLoadRateTypePeriodPropEnum = append(trafficLoadRateTypePeriodPropEnum, v)
	}
}

const (

	// TrafficLoadRatePeriodSecond captures enum value "second"
	TrafficLoadRatePeriodSecond string = "second"

	// TrafficLoadRatePeriodMinute captures enum value "minute"
	TrafficLoadRatePeriodMinute string = "minute"

	// TrafficLoadRatePeriodHour captures enum value "hour"
	TrafficLoadRatePeriodHour string = "hour"
)

// prop value enum
func (m *TrafficLoadRate) validatePeriodEnum(path, location string, value string) error {
	if err := validate.EnumCase(path, location, value, trafficLoadRateTypePeriodPropEnum, true); err != nil {
		return err
	}
	return nil
}

func (m *TrafficLoadRate) validatePeriod(formats strfmt.Registry) error {

	if err := validate.Required("rate"+"."+"period", "body", m.Period); err != nil {
		return err
	}

	// value enum
	if err := m.validatePeriodEnum("rate"+"."+"period", "body", *m.Period); err != nil {
		return err
	}

	return nil
}

func (m *TrafficLoadRate) validateValue(formats strfmt.Registry) error {

	if err := validate.Required("rate"+"."+"value", "body", m.Value); err != nil {
		return err
	}

	if err := validate.MinimumInt("rate"+"."+"value", "body", *m.Value, 1, false); err != nil {
		return err
	}

	return nil
}

// ContextValidate validates this traffic load rate based on context it is used
func (m *TrafficLoadRate) ContextValidate(ctx context.Context, formats strfmt.Registry) error {
	return nil
}

// MarshalBinary interface implementation
func (m *TrafficLoadRate) MarshalBinary() ([]byte, error) {
	if m == nil {
		return nil, nil
	}
	return swag.WriteJSON(m)
}

// UnmarshalBinary interface implementation
func (m *TrafficLoadRate) UnmarshalBinary(b []byte) error {
	var res TrafficLoadRate
	if err := swag.ReadJSON(b, &res); err != nil {
		return err
	}
	*m = res
	return nil
}